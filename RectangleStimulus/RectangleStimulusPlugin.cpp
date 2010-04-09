/*
 *  RectangleStimulusPlugins.cpp
 *  RectangleStimulusPlugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include "RectangleStimulusPlugin.h"
#include "RectangleStimulusFactory.h"
#include "MWorksCore/ComponentFactory.h"
using namespace mw;

Plugin *getPlugin(){
    return new mRectangleStimulusPlugin();
}


void mRectangleStimulusPlugin::registerComponents(shared_ptr<ComponentRegistry> registry) {
	registry->registerFactory(std::string("stimulus/rectangle"),
							  (ComponentFactory *)(new mRectangleStimulusFactory()));
}
