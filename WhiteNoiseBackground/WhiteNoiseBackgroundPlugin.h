/*
 *  WhiteNoiseBackgroundPlugin.h
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#ifndef WhiteNoiseBackground_PLUGIN_H_
#define WhiteNoiseBackground_PLUGIN_H_

#include <MWorksCore/Plugin.h>

using namespace mw;


extern "C" {
    Plugin* getPlugin();
}


class WhiteNoiseBackgroundPlugin : public Plugin {
    virtual void registerComponents(shared_ptr<ComponentRegistry> registry);
};


#endif
