/*
 *  PlayMovie.cpp
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "PlayMovie.h"

PlayMovie::PlayMovie(shared_ptr<MovieStimulus> the_movie) : 
Action() 
{
	setName("PlayMovie");
	movie=the_movie;
}

bool PlayMovie::execute() {	
	movie->play();
    return true;
}

shared_ptr<mw::Component> PlayMovieFactory::createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg) {
	
	const char *MOVIE = "movie";
	
	REQUIRE_ATTRIBUTES(parameters, MOVIE);
	
	shared_ptr <MovieStimulus> the_movie = reg->getObject<MovieStimulus>(parameters.find(MOVIE)->second);
	
	if(the_movie == 0) {
		throw MissingReferenceException(parameters.find("reference_id")->second, MOVIE, parameters.find(MOVIE)->second);		
	}
	
	shared_ptr <PlayMovie> new_play_movie_action = shared_ptr<PlayMovie>(new PlayMovie(the_movie));
	return new_play_movie_action;		
}


