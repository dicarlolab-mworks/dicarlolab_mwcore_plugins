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
#include "RandomizeBackground.h"

using namespace mw;


shared_ptr<mw::Component> WhiteNoiseBackgroundFactory::createObject(std::map<std::string, std::string> parameters,
                                                                    ComponentRegistry *reg)
{
    const char* TAG = "tag";

    REQUIRE_ATTRIBUTES(parameters,
                       TAG);
    
    std::string tag(parameters[TAG]);
    
    shared_ptr<WhiteNoiseBackground> newComponent(new WhiteNoiseBackground(tag));
    
    newComponent->load(StimulusDisplay::getCurrentStimulusDisplay());
    shared_ptr<StimulusNode> node(new StimulusNode(newComponent));
    reg->registerStimulusNode(tag, node);
    
    return newComponent;
}


shared_ptr<mw::Component> RandomizeBackgroundFactory::createObject(std::map<std::string, std::string> parameters,
                                                                   ComponentRegistry *reg)
{
    const char* STIMULUS = "stimulus";
    
    REQUIRE_ATTRIBUTES(parameters, STIMULUS);
    
    shared_ptr<StimulusNode> backgroundNode = reg->getStimulus(parameters[STIMULUS]);
    CHECK_ATTRIBUTE(backgroundNode, parameters, STIMULUS);
    
    shared_ptr<RandomizeBackground> newComponent(new RandomizeBackground(backgroundNode));
    return newComponent;
}






















