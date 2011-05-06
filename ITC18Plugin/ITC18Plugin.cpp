/*
 *  ITC18Plugins.cpp
 *  ITC18Plugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include <MWorksCore/Plugin.h>
#include <MWorksCore/StandardComponentFactory.h>

#include "ITC18_IODevice.h"

using namespace mw;


class ITC18Plugin : public Plugin {
	virtual void registerComponents(shared_ptr<ComponentRegistry> registry) {
        registry->registerFactory<StandardComponentFactory, mITC18_IODevice>();
        registry->registerFactory<StandardComponentFactory, IOChannelRequest_TriggeredAnalogSnippetITC18>();
    }
};


extern "C" Plugin* getPlugin() {
    return new ITC18Plugin();
}
