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

#define STIM_MOVIE_LOOP "loop"
#define STIM_MOVIE_PLAYING "playing"
#define STIM_MOVIE_CURRENT_FRAME "current_frame"
#define STIM_MOVIE_CURRENT_STIMULUS "current_stimulus"

#define STIM_TYPE_MOVIE "movie"
#define STIM_MOVIE_STIMULUS_GROUP "stimulus_group"

#define STIM_TYPE_IMAGE_DIRECTORY_MOVIE "image_directory_movie"
#define STIM_MOVIE_DIRECTORY_PATH "directory_path"


const std::string BaseMovieStimulus::ENDED("ended");
const std::string BaseMovieStimulus::LOOP("loop");


void BaseMovieStimulus::describeComponent(ComponentInfo &info) {
    StandardDynamicStimulus::describeComponent(info);
    info.addParameter(ENDED, false);
    info.addParameter(LOOP, "0");
}


BaseMovieStimulus::BaseMovieStimulus(const ParameterValueMap &parameters) :
    StandardDynamicStimulus(parameters),
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


int BaseMovieStimulus::getFrameNumber() {
    int frameNumber = StandardDynamicStimulus::getFrameNumber();
    
    if ((frameNumber >= 0) && bool(loop->getValue())) {
        frameNumber %= getNumFrames();
    }

    return frameNumber;
}


bool BaseMovieStimulus::needDraw() {
    return StandardDynamicStimulus::needDraw() && (getFrameNumber() <= getNumFrames());
}


void BaseMovieStimulus::drawFrame(shared_ptr<StimulusDisplay> display, int frameNumber) {    
    int numFrames = getNumFrames();
    if (frameNumber < numFrames) {
        getStimulusForFrame(frameNumber)->draw(display);
    } else if (frameNumber == numFrames) {
        if (ended != NULL) {
            ended->setValue(true);
        }
    }
}


Datum BaseMovieStimulus::getCurrentAnnounceDrawData() {
    Datum announceData = StandardDynamicStimulus::getCurrentAnnounceDrawData();

    announceData.addElement(STIM_MOVIE_LOOP, loop->getValue());  
    announceData.addElement(STIM_MOVIE_PLAYING, Datum(started));  

    int frameNumber = getFrameNumber();
    announceData.addElement(STIM_MOVIE_CURRENT_FRAME, Datum((long)frameNumber));
    if ((frameNumber >= 0) && (frameNumber < getNumFrames())) {
        announceData.addElement(STIM_MOVIE_CURRENT_STIMULUS,
                                getStimulusForFrame(frameNumber)->getCurrentAnnounceDrawData());
    } else {
        announceData.addElement(STIM_MOVIE_CURRENT_STIMULUS, Datum(0L));
    }

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
    
    announceData.addElement(STIM_TYPE, STIM_TYPE_MOVIE);  
    announceData.addElement(STIM_MOVIE_STIMULUS_GROUP, stimulusGroup->getTag());  
    
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
    directoryPath(mw::expandPath(parameters["working_path"], parameters[DIRECTORY_PATH]).string())
{
    std::vector<std::string> imageFilePaths;
    mw::getFilePaths(directoryPath, imageFilePaths);
    std::sort(imageFilePaths.begin(), imageFilePaths.end());
    
    ComponentRegistryPtr reg = parameters[DIRECTORY_PATH].getRegistry();
    
    for (size_t i = 0; i < imageFilePaths.size(); i++) {
        std::string imageTag((boost::format("%1%_frame_%2%") % tag % i).str());
        
        ParameterValueMap imageParams(parameters);
        imageParams.at(TAG) = ParameterValue(imageTag, reg);
        imageParams.insert(std::make_pair(ImageStimulus::PATH, ParameterValue(imageFilePaths[i], reg)));
        
        images.push_back(shared_ptr<ImageStimulus>(new ImageStimulus(imageParams)));
    }
}


Datum ImageDirectoryMovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, STIM_TYPE_IMAGE_DIRECTORY_MOVIE);  
    announceData.addElement(STIM_MOVIE_DIRECTORY_PATH, directoryPath);  
    
    return announceData;
}























