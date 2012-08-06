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
#include "ImageDirectoryMovieStimulus.h"


class MovieStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardStimulusFactory, MovieStimulus>();
        registry->registerFactory<StandardStimulusFactory, ImageDirectoryMovieStimulus>();
    }
};


extern "C" Plugin* getPlugin() {
    return new MovieStimulusPlugin();
}
