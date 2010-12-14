/*
 *  MovieStimulus.cpp
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "MovieStimulus.h"

#define STIM_TYPE_MOVIE "movie"
#define STIM_MOVIE_PLAYING "playing"
#define STIM_MOVIE_CURRENT_FRAME "current_frame"

MovieStimulus::MovieStimulus(const std::string &_tag,
                             shared_ptr<Variable> _frames_per_second,
                             shared_ptr<StimulusGroup> _stimulus_group,
                             shared_ptr<Variable> ended,
                             shared_ptr<Variable> loop) :
    StandardDynamicStimulus(_tag, _frames_per_second),
    stimulus_group(_stimulus_group),
    ended(ended),
    loop(loop)
{
}

int MovieStimulus::getFrameNumber() {
    int frameNumber = DynamicStimulusDriver::getFrameNumber();
    
    if (bool(loop->getValue())) {
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
	announceData.addElement(STIM_MOVIE_PLAYING, Datum(started));  
	announceData.addElement(STIM_MOVIE_CURRENT_FRAME, Datum((long)getFrameNumber()));  
	return (announceData);
}

shared_ptr<mw::Component> MovieStimulusFactory::createObject(std::map<std::string, std::string> parameters,
														   ComponentRegistry *reg) {
	const char *TAG = "tag";
	const char *STIMULUS_GROUP = "stimulus_group";
	const char *FRAMES_PER_SECOND = "frames_per_second";
	const char *ENDED = "ended";
	const char *LOOP = "loop";
	
	REQUIRE_ATTRIBUTES(parameters, 
					   TAG, 
					   STIMULUS_GROUP,
					   FRAMES_PER_SECOND);
	
	std::string tagname(parameters.find(TAG)->second);
	
	boost::shared_ptr<StimulusGroup> the_group = reg->getObject<StimulusGroup>(parameters.find(STIMULUS_GROUP)->second);
	if(the_group == 0) {
		throw MissingReferenceException(parameters.find("reference_id")->second, STIMULUS_GROUP, parameters.find(STIMULUS_GROUP)->second);		
	}	
	
	shared_ptr<Variable> frames_per_second = reg->getVariable(parameters.find(FRAMES_PER_SECOND)->second);	
	checkAttribute(frames_per_second, parameters.find("reference_id")->second, FRAMES_PER_SECOND, parameters[FRAMES_PER_SECOND]);

    shared_ptr<Variable> ended;
    if (!(parameters[ENDED].empty())) {
        ended = reg->getVariable(parameters[ENDED]);
        CHECK_ATTRIBUTE(ended, parameters, ENDED);
    }

	shared_ptr<Variable> loop = reg->getVariable(parameters[LOOP], "0");
    CHECK_ATTRIBUTE(loop, parameters, LOOP);
	
	shared_ptr <MovieStimulus> new_movie = shared_ptr<MovieStimulus>(new MovieStimulus(tagname,
                                                                                       frames_per_second,
                                                                                       the_group,
                                                                                       ended,
                                                                                       loop));
	
	shared_ptr <StimulusNode> thisStimNode = shared_ptr<StimulusNode>(new StimulusNode(new_movie));
	reg->registerStimulusNode(tagname, thisStimNode);
	
	
	return new_movie;
}























