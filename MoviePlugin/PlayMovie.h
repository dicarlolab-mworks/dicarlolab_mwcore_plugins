/*
 *  PlayMovie.h
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/17/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef PLAY_MOVIE_ACTION_H_
#define PLAY_MOVIE_ACTION_H_

#include "MWorksCore/TrialBuildingBlocks.h"
#include "MovieStimulus.h"
using namespace mw;


class PlayMovie : public Action {	
protected:
	shared_ptr<MovieStimulus> movie;
	
public:
	
	PlayMovie(shared_ptr<MovieStimulus> the_movie);
	virtual bool execute();
};

class PlayMovieFactory : public ComponentFactory {
	virtual boost::shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg);
};


#endif 
// PLAY_MOVIE_ACTION_H_

