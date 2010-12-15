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
    // TODO: you need to customize the "signature" of the object your plugin will create
    //       The signature is of the form component/type Ð(e.g. stimulus/circle, or iodevice/NIDAQ)
    registry->registerFactory(std::string("stimulus/WhiteNoiseBackground"),
                              (ComponentFactory *)(new WhiteNoiseBackgroundFactory()));
}
