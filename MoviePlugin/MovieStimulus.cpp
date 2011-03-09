/*
 *  MovieStimulus.cpp
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "MovieStimulus.h"

#include <algorithm>

#define STIM_MOVIE_LOOP "loop"
#define STIM_MOVIE_PLAYING "playing"
#define STIM_MOVIE_CURRENT_FRAME "current_frame"
#define STIM_MOVIE_CURRENT_STIMULUS "current_stimulus"

#define STIM_TYPE_MOVIE "movie"
#define STIM_MOVIE_STIMULUS_GROUP "stimulus_group"

#define STIM_TYPE_IMAGE_DIRECTORY_MOVIE "image_directory_movie"
#define STIM_MOVIE_DIRECTORY_PATH "directory_path"


BaseMovieStimulus::BaseMovieStimulus(const std::string &tag,
                                     shared_ptr<Variable> framesPerSecond,
                                     shared_ptr<Variable> ended,
                                     shared_ptr<Variable> loop) :
    StandardDynamicStimulus(tag, framesPerSecond),
    ended(ended),
    loop(registerVariable(loop))
{ }


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
        int numFrames = getNumFrames();
        frameNumber %= numFrames;
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


MovieStimulus::MovieStimulus(const std::string &tag,
                             shared_ptr<Variable> framesPerSecond,
                             shared_ptr<StimulusGroup> stimulusGroup,
                             shared_ptr<Variable> ended,
                             shared_ptr<Variable> loop) :
    BaseMovieStimulus(tag, framesPerSecond, ended, loop),
    stimulusGroup(stimulusGroup)
{ }


Datum MovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, STIM_TYPE_MOVIE);  
    announceData.addElement(STIM_MOVIE_STIMULUS_GROUP, stimulusGroup->getTag());  
    
    return announceData;
}


ImageDirectoryMovieStimulus::ImageDirectoryMovieStimulus(const std::string &tag,
                                                         const std::string &directoryPath,
                                                         shared_ptr<Variable> xSize,
                                                         shared_ptr<Variable> ySize,
                                                         shared_ptr<Variable> xPosition,
                                                         shared_ptr<Variable> yPosition,
                                                         shared_ptr<Variable> rotation,
                                                         shared_ptr<Variable> alphaMultiplier,
                                                         shared_ptr<Variable> framesPerSecond,
                                                         shared_ptr<Variable> ended,
                                                         shared_ptr<Variable> loop) :
    BaseMovieStimulus(tag, framesPerSecond, ended, loop),
    directoryPath(directoryPath)
{
    std::vector<std::string> imageFilePaths;

    if (!mw::getFilePaths(directoryPath, imageFilePaths)) {
        throw SimpleException("Invalid directory path", directoryPath);
    }
    
    std::sort(imageFilePaths.begin(), imageFilePaths.end());
    
    for (size_t i = 0; i < imageFilePaths.size(); i++) {
        std::string imageTag((boost::format("%1%_frame_%2%") % tag % i).str());
        images.push_back(shared_ptr<ImageStimulus>(new ImageStimulus(imageTag,
                                                                     imageFilePaths[i],
                                                                     xPosition,
                                                                     yPosition,
                                                                     xSize,
                                                                     ySize,
                                                                     rotation,
                                                                     alphaMultiplier)));
    }
}


Datum ImageDirectoryMovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, STIM_TYPE_IMAGE_DIRECTORY_MOVIE);  
    announceData.addElement(STIM_MOVIE_DIRECTORY_PATH, directoryPath);  
    
    return announceData;
}























