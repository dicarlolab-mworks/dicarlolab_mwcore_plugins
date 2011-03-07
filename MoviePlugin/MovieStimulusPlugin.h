/*
 *  MovieStimulusPlugins.h
 *  MovieStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef MovieStimulusPlugin_PLUGIN_H_
#define MovieStimulusPlugin_PLUGIN_H_

#include <MWorksCore/Plugin.h>

using namespace mw;


extern "C" {
    Plugin* getPlugin();
}


class MovieStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry);
};


#endif
