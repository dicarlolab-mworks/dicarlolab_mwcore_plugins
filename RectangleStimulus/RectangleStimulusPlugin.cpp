/*
 *  RectangleStimulusPlugins.cpp
 *  RectangleStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include <MWorksCore/Plugin.h>
#include <MWorksCore/StandardStimulusFactory.h>

#include "RectangleStimulus.h"

using namespace mw;


class RectangleStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardStimulusFactory, RectangleStimulus>();
    }	
};


extern "C" Plugin* getPlugin(){
    return new RectangleStimulusPlugin();
}
