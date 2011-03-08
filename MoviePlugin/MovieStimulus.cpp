/*
 *  MovieStimulus.cpp
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "MovieStimulus.h"

#include <MWorksCore/ComponentRegistry.h>

using namespace mw;

#define STIM_MOVIE_LOOP "loop"
#define STIM_MOVIE_PLAYING "playing"
#define STIM_MOVIE_CURRENT_FRAME "current_frame"
#define STIM_MOVIE_CURRENT_STIMULUS "current_stimulus"

#define STIM_TYPE_MOVIE "movie"
#define STIM_MOVIE_STIMULUS_GROUP "stimulus_group"

#define STIM_TYPE_IMAGE_DIRECTORY_MOVIE "image_directory_movie"
#define STIM_MOVIE_DIRECTORY_PATH "path"


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
{ }


Datum ImageDirectoryMovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = BaseMovieStimulus::getCurrentAnnounceDrawData();
    
    announceData.addElement(STIM_TYPE, STIM_TYPE_IMAGE_DIRECTORY_MOVIE);  
    announceData.addElement(STIM_MOVIE_DIRECTORY_PATH, directoryPath);  
    
    return announceData;
}


void BaseMovieStimulusFactory::getBaseMovieParameters(std::map<std::string, std::string> &parameters,
                                                      ComponentRegistry *reg,
                                                      std::string &tag,
                                                      shared_ptr<Variable> &framesPerSecond,
                                                      shared_ptr<Variable> &ended,
                                                      shared_ptr<Variable> &loop)
{
    const char *TAG = "tag";
    const char *FRAMES_PER_SECOND = "frames_per_second";
    const char *ENDED = "ended";
    const char *LOOP = "loop";
    
    REQUIRE_ATTRIBUTES(parameters,
                       TAG,
                       FRAMES_PER_SECOND);
    
    tag = parameters[TAG];
    
    framesPerSecond = reg->getVariable(parameters[FRAMES_PER_SECOND]);
    CHECK_ATTRIBUTE(framesPerSecond, parameters, FRAMES_PER_SECOND);
    
    if (!(parameters[ENDED].empty())) {
        ended = reg->getVariable(parameters[ENDED]);
        CHECK_ATTRIBUTE(ended, parameters, ENDED);
    }
    
    loop = reg->getVariable(parameters[LOOP], "0");
    CHECK_ATTRIBUTE(loop, parameters, LOOP);
}


shared_ptr<mw::Component> MovieStimulusFactory::createObject(std::map<std::string, std::string> parameters,
                                                             ComponentRegistry *reg)
{
    const char *STIMULUS_GROUP = "stimulus_group";
    
    REQUIRE_ATTRIBUTES(parameters, STIMULUS_GROUP);
    
    std::string tag;
    shared_ptr<Variable> framesPerSecond;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    getBaseMovieParameters(parameters, reg, tag, framesPerSecond, ended, loop);
    
    shared_ptr<StimulusGroup> stimulusGroup(reg->getObject<StimulusGroup>(parameters[STIMULUS_GROUP]));
    CHECK_ATTRIBUTE(stimulusGroup, parameters, STIMULUS_GROUP);
    
    shared_ptr<MovieStimulus> newMovie(new MovieStimulus(tag,
                                                         framesPerSecond,
                                                         stimulusGroup,
                                                         ended,
                                                         loop));
    
    // To preserve existing behavior, *do not* load stimulus here
    shared_ptr<StimulusNode> node(new StimulusNode(newMovie));
    reg->registerStimulusNode(tag, node);
    
    return newMovie;
}


shared_ptr<mw::Component>
ImageDirectoryMovieStimulusFactory::createObject(std::map<std::string, std::string> parameters, ComponentRegistry *reg)
{
    const char *PATH = "path";
    const char *X_SIZE = "x_size";
    const char *Y_SIZE = "y_size";
    const char *X_POSITION = "x_position";
    const char *Y_POSITION = "y_position";
    const char *ROTATION = "rotation";
    const char *ALPHA_MULTIPLIER = "alpha_multiplier";
    const char *DEFERRED = "deferred";
    
    REQUIRE_ATTRIBUTES(parameters,
                       PATH,
                       X_SIZE,
                       Y_SIZE);
    
    std::string tag;
    shared_ptr<Variable> framesPerSecond;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    getBaseMovieParameters(parameters, reg, tag, framesPerSecond, ended, loop);
    
    boost::filesystem::path directoryPath(reg->getPath(parameters["working_path"], parameters[PATH]));
    
    shared_ptr<Variable> xSize(reg->getVariable(parameters[X_SIZE]));
    CHECK_ATTRIBUTE(xSize, parameters, X_SIZE);
    
    shared_ptr<Variable> ySize(reg->getVariable(parameters[Y_SIZE]));
    CHECK_ATTRIBUTE(ySize, parameters, Y_SIZE);
    
    shared_ptr<Variable> xPosition(reg->getVariable(parameters[X_POSITION], "0.0"));
    CHECK_ATTRIBUTE(xPosition, parameters, X_POSITION);
    
    shared_ptr<Variable> yPosition(reg->getVariable(parameters[Y_POSITION], "0.0"));
    CHECK_ATTRIBUTE(yPosition, parameters, Y_POSITION);
    
    shared_ptr<Variable> rotation(reg->getVariable(parameters[ROTATION], "0.0"));
    CHECK_ATTRIBUTE(rotation, parameters, ROTATION);
    
    shared_ptr<Variable> alphaMultiplier(reg->getVariable(parameters[ALPHA_MULTIPLIER], "1.0"));
    CHECK_ATTRIBUTE(alphaMultiplier, parameters, ALPHA_MULTIPLIER);
    
    shared_ptr<ImageDirectoryMovieStimulus> newMovie(new ImageDirectoryMovieStimulus(tag,
                                                                                     directoryPath.string(),
                                                                                     xSize,
                                                                                     ySize,
                                                                                     xPosition,
                                                                                     yPosition,
                                                                                     rotation,
                                                                                     alphaMultiplier,
                                                                                     framesPerSecond,
                                                                                     ended,
                                                                                     loop));
    
    newMovie->setDeferredFromString(parameters[DEFERRED]);
    if (newMovie->getDeferred() == Stimulus::nondeferred_load) {
        newMovie->load(StimulusDisplay::getCurrentStimulusDisplay());
    }

    shared_ptr<StimulusNode> node(new StimulusNode(newMovie));
    reg->registerStimulusNode(tag, node);
    
    return newMovie;
}























