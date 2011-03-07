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

#define STIM_TYPE_MOVIE "movie"
#define STIM_MOVIE_STIMULUS_GROUP "stimulus_group"
#define STIM_MOVIE_LOOP "loop"
#define STIM_MOVIE_PLAYING "playing"
#define STIM_MOVIE_CURRENT_FRAME "current_frame"
#define STIM_MOVIE_CURRENT_STIMULUS "current_stimulus"


BaseMovieStimulus::BaseMovieStimulus(const std::string &tag,
                                     shared_ptr<Variable> framesPerSecond,
                                     shared_ptr<Variable> ended,
                                     shared_ptr<Variable> loop) :
    StandardDynamicStimulus(tag, framesPerSecond),
    ended(ended),
    loop(loop)
{ }


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
    int frameNumber = DynamicStimulusDriver::getFrameNumber();
    
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


shared_ptr<mw::Component> MovieStimulusFactory::createObject(std::map<std::string, std::string> parameters,
                                                             ComponentRegistry *reg)
{
    const char *TAG = "tag";
    const char *STIMULUS_GROUP = "stimulus_group";
    const char *FRAMES_PER_SECOND = "frames_per_second";
    const char *ENDED = "ended";
    const char *LOOP = "loop";
    
    REQUIRE_ATTRIBUTES(parameters, 
                       TAG, 
                       STIMULUS_GROUP,
                       FRAMES_PER_SECOND);
    
    std::string tagname(parameters[TAG]);
    
    shared_ptr<StimulusGroup> stimulusGroup(reg->getObject<StimulusGroup>(parameters[STIMULUS_GROUP]));
    CHECK_ATTRIBUTE(stimulusGroup, parameters, STIMULUS_GROUP);
    
    shared_ptr<Variable> framesPerSecond(reg->getVariable(parameters[FRAMES_PER_SECOND]));    
    CHECK_ATTRIBUTE(framesPerSecond, parameters, FRAMES_PER_SECOND);

    shared_ptr<Variable> ended;
    if (!(parameters[ENDED].empty())) {
        ended = reg->getVariable(parameters[ENDED]);
        CHECK_ATTRIBUTE(ended, parameters, ENDED);
    }

    shared_ptr<Variable> loop(reg->getVariable(parameters[LOOP], "0"));
    CHECK_ATTRIBUTE(loop, parameters, LOOP);
    
    shared_ptr <MovieStimulus> new_movie = shared_ptr<MovieStimulus>(new MovieStimulus(tagname,
                                                                                       framesPerSecond,
                                                                                       stimulusGroup,
                                                                                       ended,
                                                                                       loop));
    
    shared_ptr <StimulusNode> thisStimNode(new StimulusNode(new_movie));
    reg->registerStimulusNode(tagname, thisStimNode);
    
    return new_movie;
}























