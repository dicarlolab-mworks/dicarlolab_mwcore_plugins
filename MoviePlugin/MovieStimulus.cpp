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
                             shared_ptr<StimulusGroup> _stimulus_group) :
    StandardDynamicStimulus(_tag, _frames_per_second)
{
	stimulus_group = _stimulus_group;
}

bool MovieStimulus::needDraw() {
    return StandardDynamicStimulus::needDraw() && (getFrameNumber() < stimulus_group->getNElements());
}

void MovieStimulus::drawFrame(shared_ptr<StimulusDisplay> display, int frameNumber) {	
    if (frameNumber < stimulus_group->getNElements()) {
        stimulus_group->getElement(frameNumber)->draw(display);
    }
}

Datum MovieStimulus::getCurrentAnnounceDrawData() {
	boost::mutex::scoped_lock locker(stim_lock);
	Datum announceData = DynamicStimulusDriver::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_NAME,tag);
	announceData.addElement(STIM_TYPE,STIM_TYPE_MOVIE);  
	announceData.addElement(STIM_MOVIE_PLAYING, Datum(started));  
	announceData.addElement(STIM_MOVIE_CURRENT_FRAME, Datum((long)getFrameNumber()));  
	return (announceData);
}

shared_ptr<mw::Component> MovieStimulusFactory::createObject(std::map<std::string, std::string> parameters,
														   ComponentRegistry *reg) {
	const char *TAG = "tag";
	const char *STIMULUS_GROUP = "stimulus_group";
	const char *FRAMES_PER_SECOND = "frames_per_second";
	
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
	
	shared_ptr <MovieStimulus> new_movie = shared_ptr<MovieStimulus>(new MovieStimulus(tagname,
                                                                                       frames_per_second,
                                                                                       the_group));
	
	shared_ptr <StimulusNode> thisStimNode = shared_ptr<StimulusNode>(new StimulusNode(new_movie));
	reg->registerStimulusNode(tagname, thisStimNode);
	
	
	return new_movie;
}
