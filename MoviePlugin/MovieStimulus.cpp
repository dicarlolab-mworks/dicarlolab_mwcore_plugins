/*
 *  MovieStimulus.cpp
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "MovieStimulus.h"

#include <MWorksCore/StandardStimuli.h>

#include <algorithm>


const std::string BaseMovieStimulus::FRAMES_PER_SECOND("frames_per_second");
const std::string BaseMovieStimulus::ENDED("ended");
const std::string BaseMovieStimulus::LOOP("loop");


void BaseMovieStimulus::describeComponent(ComponentInfo &info) {
    StandardDynamicStimulus::describeComponent(info);
    info.addParameter(FRAMES_PER_SECOND);
    info.addParameter(ENDED, false);
    info.addParameter(LOOP, "0");
}


BaseMovieStimulus::BaseMovieStimulus(const ParameterValueMap &parameters) :
    StandardDynamicStimulus(parameters),
    framesPerSecond(registerVariable(parameters[FRAMES_PER_SECOND])),
    loop(registerVariable(parameters[LOOP]))
{
    if (!(parameters[ENDED].empty())) {
        ended = parameters[ENDED];
    }
}


void BaseMovieStimulus::freeze(bool shouldFreeze) {
    StandardDynamicStimulus::freeze(shouldFreeze);
    for (int i = 0; i < getNumFrames(); i++) {
        getStimulusForFrame(i)->freeze(shouldFreeze);
    }
}


void BaseMovieStimulus::load(shared_ptr<StimulusDisplay> display) {
    for (int i = 0; i < getNumFrames(); i++) {
        getStimulusForFrame(i)->load(display);
    }
}


void BaseMovieStimulus::unload(shared_ptr<StimulusDisplay> display) {
    for (int i = 0; i < getNumFrames(); i++) {
        getStimulusForFrame(i)->unload(display);
    }
}


void BaseMovieStimulus::startPlaying() {
    const double frameRate = framesPerSecond->getValue().getFloat();
    const double refreshRate = StimulusDisplay::getCurrentStimulusDisplay()->getMainDisplayRefreshRate();
    
    if ((frameRate > refreshRate) || (fmod(refreshRate, frameRate) != 0.0)) {
        mwarning(M_DISPLAY_MESSAGE_DOMAIN,
                 "Requested frame rate (%g) is incompatible with display refresh rate (%g)",
                 frameRate,
                 refreshRate);

    }
    
    framesPerUS = frameRate / 1.0e6;
    lastFrameDrawn = -1;
    
    StandardDynamicStimulus::startPlaying();
}


int BaseMovieStimulus::getFrameNumber() {
    if (!isPlaying()) {
        return -1;
    }
    
    int frameNumber = int(double(getElapsedTime()) * framesPerUS);
    
    if (bool(loop->getValue())) {
        frameNumber %= getNumFrames();
    }

    return frameNumber;
}


bool BaseMovieStimulus::needDraw() {
    int frameNumber = getFrameNumber();
    return StandardDynamicStimulus::needDraw() && (frameNumber != lastFrameDrawn) && (frameNumber <= getNumFrames());
}


void BaseMovieStimulus::drawFrame(shared_ptr<StimulusDisplay> display) {
    int frameNumber = getFrameNumber();
    int numFrames = getNumFrames();
    if (frameNumber < numFrames) {
        getStimulusForFrame(frameNumber)->draw(display);
        lastFrameDrawn = frameNumber;
    } else if (frameNumber == numFrames) {
        if (ended != NULL) {
            ended->setValue(true);
        }
    }
}


Datum BaseMovieStimulus::getCurrentAnnounceDrawData() {
    Datum announceData = StandardDynamicStimulus::getCurrentAnnounceDrawData();

    announceData.addElement(FRAMES_PER_SECOND, framesPerSecond->getValue().getInteger());  
    announceData.addElement(LOOP, loop->getValue());  
    announceData.addElement("playing", Datum(isPlaying()));  

    int frameNumber = getFrameNumber();
    announceData.addElement("current_frame", Datum((long)frameNumber));
    
    Datum currentStimulusAnnounceData(0L);
    if ((frameNumber >= 0) && (frameNumber < getNumFrames())) {
        currentStimulusAnnounceData = getStimulusForFrame(frameNumber)->getCurrentAnnounceDrawData();
    }
    announceData.addElement("current_stimulus", currentStimulusAnnounceData);

    return announceData;
}


const std::string MovieStimulus::STIMULUS_GROUP("stimulus_group");


void MovieStimulus::describeComponent(ComponentInfo &info) {
    BaseMovieStimulus::describeComponent(info);
    info.setSignature("stimulus/movie");
    info.addParameter(STIMULUS_GROUP);
}


MovieStimulus::MovieStimulus(const ParameterValueMap &parameters) :
    BaseMovieStimulus(parameters),
    stimulusGroup(parameters[STIMULUS_GROUP])
{
    // To preserve existing behavior, do not auto-load stimulus
    setDeferred(explicit_load);
}


Datum MovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, "movie");  
    announceData.addElement(STIMULUS_GROUP, stimulusGroup->getTag());  
    
    return announceData;
}


const std::string ImageDirectoryMovieStimulus::DIRECTORY_PATH("directory_path");


void ImageDirectoryMovieStimulus::describeComponent(ComponentInfo &info) {
    BaseMovieStimulus::describeComponent(info);
    info.setSignature("stimulus/image_directory_movie");
    info.addParameter(DIRECTORY_PATH);

    // Add all ImageStimulus parameters except "path"
    ComponentInfo imageInfo;
    ImageStimulus::describeComponent(imageInfo);
    const ParameterInfoMap &imageParams = imageInfo.getParameters();
    for (ParameterInfoMap::const_iterator iter = imageParams.begin(); iter != imageParams.end(); iter++) {
        const std::string &name = (*iter).first;
        if (name != ImageStimulus::PATH) {
            info.addParameter(name, (*iter).second);
        }
    }
}


ImageDirectoryMovieStimulus::ImageDirectoryMovieStimulus(const ParameterValueMap &parameters) :
    BaseMovieStimulus(parameters),
    directoryPath(parameters[DIRECTORY_PATH].as<boost::filesystem::path>().string())
{
    std::vector<std::string> imageFilePaths;
    mw::getFilePaths(directoryPath, imageFilePaths);
    std::sort(imageFilePaths.begin(), imageFilePaths.end());
    
    ComponentRegistryPtr reg = parameters[DIRECTORY_PATH].getRegistry();
    
    for (size_t i = 0; i < imageFilePaths.size(); i++) {
        std::string imageTag((boost::format("%1%_frame_%2%") % getTag() % i).str());
        
        ParameterValueMap imageParams(parameters);
        imageParams.at(TAG) = ParameterValue(imageTag, reg);
        imageParams.insert(std::make_pair(ImageStimulus::PATH, ParameterValue(imageFilePaths[i], reg)));
        
        images.push_back(shared_ptr<ImageStimulus>(new ImageStimulus(imageParams)));
    }
}


Datum ImageDirectoryMovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, "image_directory_movie");  
    announceData.addElement(DIRECTORY_PATH, directoryPath);  
    
    return announceData;
}























