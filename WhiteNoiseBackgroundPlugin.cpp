/*
 *  WhiteNoiseBackgroundPlugin.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include <MWorksCore/ComponentFactory.h>

#include "WhiteNoiseBackgroundPlugin.h"
#include "WhiteNoiseBackgroundFactory.h"

using namespace mw;


Plugin* getPlugin() {
    return new WhiteNoiseBackgroundPlugin();
}


void WhiteNoiseBackgroundPlugin::registerComponents(shared_ptr<ComponentRegistry> registry) {
    registry->registerFactory(std::string("stimulus/white_noise_background"),
                              (ComponentFactory *)(new WhiteNoiseBackgroundFactory()));
    registry->registerFactory(std::string("action/randomize_background"),
                              (ComponentFactory *)(new RandomizeBackgroundFactory()));
}
