/*
 *  CircleStimulusPlugins.cpp
 *  CircleStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include <MWorksCore/Plugin.h>
#include <MWorksCore/StandardStimulusFactory.h>

#include "CircleStimulus.h"

using namespace mw;


class CircleStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardStimulusFactory, CircleStimulus>();
    }	
};


extern "C" Plugin* getPlugin(){
    return new CircleStimulusPlugin();
}
