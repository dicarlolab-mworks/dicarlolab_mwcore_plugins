/*
 *  RandomizeBackground.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/17/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include "RandomizeBackground.h"

#include "WhiteNoiseBackground.h"


RandomizeBackground::RandomizeBackground(shared_ptr<StimulusNode> backgroundNode) :
    backgroundNode(backgroundNode)
{
    setName("RandomizeBackground");
}


bool RandomizeBackground::execute() {
    shared_ptr<WhiteNoiseBackground> background(dynamic_pointer_cast<WhiteNoiseBackground>(backgroundNode->getStimulus()));
    
    if (!background) {
        merror(M_PARADIGM_MESSAGE_DOMAIN, "Invalid target for randomize_background.  Doing nothing.");
        return false;
    }
    
    background->randomizePixels();
    return true;
}
