/*
 *  MovieStimulusPlugins.cpp
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include <MWorksCore/Plugin.h>
#include <MWorksCore/StandardStimulusFactory.h>

#include "MovieStimulus.h"
#include "PlayMovie.h"
#include "StopMovie.h"

using namespace mw;


class MovieStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardStimulusFactory, MovieStimulus>();
        registry->registerFactory<StandardStimulusFactory, ImageDirectoryMovieStimulus>();
        
        registry->registerFactory(std::string("action/play_movie"),
                                  (ComponentFactory *)(new PlayMovieFactory()));
        
        registry->registerFactory(std::string("action/stop_movie"),
                                  (ComponentFactory *)(new StopMovieFactory()));
    }
};


extern "C" Plugin* getPlugin() {
    return new MovieStimulusPlugin();
}
