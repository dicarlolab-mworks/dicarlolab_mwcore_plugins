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
	
	shared_ptr <MovieStimulus> the_movie = reg->getObject<MovieStimulus>(parameters.find(MOVIE)->second);
	
	if(the_movie == 0) {
		throw MissingReferenceException(parameters.find("reference_id")->second, MOVIE, parameters.find(MOVIE)->second);		
	}
	
	shared_ptr <StopDynamicStimulus> new_stop_movie_action = shared_ptr<StopDynamicStimulus>(new StopDynamicStimulus(the_movie));
	return new_stop_movie_action;		
}
