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


MovieStimulus::MovieStimulus(const std::string &tag,
                             shared_ptr<Variable> frames_per_second,
                             shared_ptr<StimulusGroup> stimulus_group,
                             shared_ptr<Variable> ended,
                             shared_ptr<Variable> loop) :
    StandardDynamicStimulus(tag, frames_per_second),
    stimulus_group(stimulus_group),
    ended(ended),
    loop(loop)
{ }


void MovieStimulus::load(shared_ptr<StimulusDisplay> display) {
    for (int i = 0; i < stimulus_group->getNElements(); i++) {
        stimulus_group->getElement(i)->load(display);
    }
}


void MovieStimulus::unload(shared_ptr<StimulusDisplay> display) {
    for (int i = 0; i < stimulus_group->getNElements(); i++) {
        stimulus_group->getElement(i)->unload(display);
    }
}


int MovieStimulus::getFrameNumber() {
    int frameNumber = DynamicStimulusDriver::getFrameNumber();
    
    if ((frameNumber >= 0) && bool(loop->getValue())) {
        int numFrames = stimulus_group->getNElements();
        frameNumber %= numFrames;
    }

    return frameNumber;
}


bool MovieStimulus::needDraw() {
    return StandardDynamicStimulus::needDraw() && (getFrameNumber() <= stimulus_group->getNElements());
}


void MovieStimulus::drawFrame(shared_ptr<StimulusDisplay> display, int frameNumber) {    
    int numFrames = stimulus_group->getNElements();
    if (frameNumber < numFrames) {
        stimulus_group->getElement(frameNumber)->draw(display);
    } else if (frameNumber == numFrames) {
        if (ended != NULL) {
            ended->setValue(true);
        }
    }
}


Datum MovieStimulus::getCurrentAnnounceDrawData() {
    boost::mutex::scoped_lock locker(stim_lock);
    Datum announceData = StandardDynamicStimulus::getCurrentAnnounceDrawData();

    announceData.addElement(STIM_TYPE, STIM_TYPE_MOVIE);  
    announceData.addElement(STIM_MOVIE_STIMULUS_GROUP, stimulus_group->getTag());  
    announceData.addElement(STIM_MOVIE_LOOP, loop->getValue());  
    announceData.addElement(STIM_MOVIE_PLAYING, Datum(started));  

    int frameNumber = getFrameNumber();
    announceData.addElement(STIM_MOVIE_CURRENT_FRAME, Datum((long)frameNumber));
    if ((frameNumber >= 0) && (frameNumber < stimulus_group->getNElements())) {
        announceData.addElement(STIM_MOVIE_CURRENT_STIMULUS,
                                stimulus_group->getElement(frameNumber)->getCurrentAnnounceDrawData());
    } else {
        announceData.addElement(STIM_MOVIE_CURRENT_STIMULUS, Datum(0L));
    }

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
    
    shared_ptr<StimulusGroup> the_group(reg->getObject<StimulusGroup>(parameters[STIMULUS_GROUP]));
    CHECK_ATTRIBUTE(the_group, parameters, STIMULUS_GROUP);
    
    shared_ptr<Variable> frames_per_second(reg->getVariable(parameters[FRAMES_PER_SECOND]));    
    CHECK_ATTRIBUTE(frames_per_second, parameters, FRAMES_PER_SECOND);

    shared_ptr<Variable> ended;
    if (!(parameters[ENDED].empty())) {
        ended = reg->getVariable(parameters[ENDED]);
        CHECK_ATTRIBUTE(ended, parameters, ENDED);
    }

    shared_ptr<Variable> loop(reg->getVariable(parameters[LOOP], "0"));
    CHECK_ATTRIBUTE(loop, parameters, LOOP);
    
    shared_ptr <MovieStimulus> new_movie = shared_ptr<MovieStimulus>(new MovieStimulus(tagname,
                                                                                       frames_per_second,
                                                                                       the_group,
                                                                                       ended,
                                                                                       loop));
    
    shared_ptr <StimulusNode> thisStimNode(new StimulusNode(new_movie));
    reg->registerStimulusNode(tagname, thisStimNode);
    
    return new_movie;
}























