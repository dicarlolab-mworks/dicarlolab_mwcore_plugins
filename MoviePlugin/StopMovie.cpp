/*
 *  StopMovie.cpp
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "StopMovie.h"
#include "MovieStimulus.h"
#include "MWorksCore/StopDynamicStimulus.h"

shared_ptr<mw::Component> StopMovieFactory::createObject(std::map<std::string, std::string> parameters,
                                                       ComponentRegistry *reg) {
    
    mwarning(M_PLUGIN_MESSAGE_DOMAIN,
             "\"Stop Movie\" is deprecated.  Please use \"Stop Dynamic Stimulus\" instead.");
    
    const char *MOVIE = "movie";
    
    REQUIRE_ATTRIBUTES(parameters, MOVIE);
    
    shared_ptr<StimulusNode> stimNode = reg->getStimulus(parameters.find(MOVIE)->second);
    CHECK_ATTRIBUTE(stimNode, parameters, MOVIE);
    
    shared_ptr <StopDynamicStimulus> new_stop_movie_action = shared_ptr<StopDynamicStimulus>(new StopDynamicStimulus(stimNode));
    return new_stop_movie_action;        
}
