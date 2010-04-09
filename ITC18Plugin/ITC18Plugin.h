/*
 *  ITC18Plugins.h
 *  ITC18Plugins
 *
 *  Created by bkennedy on 8/14/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#include <MWorksCore/Plugin.h>
using namespace mw;

extern "C"{
    Plugin *getPlugin();
}

class ITC18Plugin : public Plugin {
    
	virtual void registerComponents(shared_ptr<ComponentRegistry> registry);	
};
