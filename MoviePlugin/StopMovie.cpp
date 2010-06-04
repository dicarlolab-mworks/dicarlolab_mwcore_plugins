/*
 *  StopMovie.cpp
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "StopMovie.h"

StopMovie::StopMovie(shared_ptr<MovieStimulus> the_movie) : 
Action() 
{
	setName("StopAndRewindMovie");
	movie=the_movie;
}

bool StopMovie::execute() {	
	movie->stopAndRewind();
    return true;
}


shared_ptr<mw::Component> StopMovieFactory::createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg) {
	
	const char *MOVIE = "movie";
	
	REQUIRE_ATTRIBUTES(parameters, MOVIE);
	
	shared_ptr <MovieStimulus> the_movie = reg->getObject<MovieStimulus>(parameters.find(MOVIE)->second);
	
	if(the_movie == 0) {
		throw MissingReferenceException(parameters.find("reference_id")->second, MOVIE, parameters.find(MOVIE)->second);		
	}
	
	shared_ptr <StopMovie> new_stop_movie_action = shared_ptr<StopMovie>(new StopMovie(the_movie));
	return new_stop_movie_action;		
}
