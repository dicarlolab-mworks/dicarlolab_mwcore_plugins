/*
 *  WhiteNoiseBackgroundFactory.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include <MWorksCore/ComponentRegistry.h>

#include "WhiteNoiseBackgroundFactory.h"
#include "WhiteNoiseBackground.h"

using namespace mw;


shared_ptr<mw::Component> WhiteNoiseBackgroundFactory::createObject(std::map<std::string, std::string> parameters,
                                                                             ComponentRegistry *reg)
{
    const char* TAG = "tag";
    const char* ANOTHER_ATTRIBUTE = "another_attribute";

    REQUIRE_ATTRIBUTES(parameters,
                       TAG,
                       ANOTHER_ATTRIBUTE);
    
    std::string tag(parameters[TAG]);
    
    shared_ptr<Variable> anotherAttribute(reg->getVariable(parameters[ANOTHER_ATTRIBUTE]));
    CHECK_ATTRIBUTE(anotherAttribute, parameters, ANOTHER_ATTRIBUTE);
    
    shared_ptr<WhiteNoiseBackground> newComponent(new WhiteNoiseBackground(tag,
                                                                                             anotherAttribute));
    
    return newComponent;
}
