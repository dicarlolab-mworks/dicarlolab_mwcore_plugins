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
using namespace mw;


class PlayMovieFactory : public ComponentFactory {
	virtual boost::shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg);
};


#endif 
// PLAY_MOVIE_ACTION_H_

