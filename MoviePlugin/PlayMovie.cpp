/*
 *  PlayMovie.cpp
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "PlayMovie.h"
#include "MovieStimulus.h"
#include "MWorksCore/PlayDynamicStimulus.h"

shared_ptr<mw::Component> PlayMovieFactory::createObject(std::map<std::string, std::string> parameters,
                                                       ComponentRegistry *reg) {
    
    mwarning(M_PLUGIN_MESSAGE_DOMAIN,
             "\"Play Movie\" is deprecated.  Please use \"Play Dynamic Stimulus\" instead.");
    
    const char *MOVIE = "movie";
    
    REQUIRE_ATTRIBUTES(parameters, MOVIE);
    
    shared_ptr<StimulusNode> stimNode = reg->getStimulus(parameters.find(MOVIE)->second);
    CHECK_ATTRIBUTE(stimNode, parameters, MOVIE);
    
    shared_ptr <PlayDynamicStimulus> new_play_movie_action = shared_ptr<PlayDynamicStimulus>(new PlayDynamicStimulus(stimNode));
    return new_play_movie_action;        
}


