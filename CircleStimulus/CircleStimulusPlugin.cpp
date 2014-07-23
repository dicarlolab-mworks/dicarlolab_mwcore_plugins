/*
 *  CircleStimulusPlugins.cpp
 *  CircleStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "CircleStimulus.h"
#include "CircularFixationPoint.h"


BEGIN_NAMESPACE_MW


class CircleStimulusPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardStimulusFactory, CircleStimulus>();
        registry->registerFactory<StandardStimulusFactory, CircularFixationPoint>();
    }
};


extern "C" Plugin* getPlugin(){
    return new CircleStimulusPlugin();
}


END_NAMESPACE_MW
