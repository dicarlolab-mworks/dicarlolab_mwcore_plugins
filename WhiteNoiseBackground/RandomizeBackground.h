/*
 *  RandomizeBackground.h
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/17/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#ifndef RandomizeBackground_H_
#define RandomizeBackground_H_

#include <MWorksCore/TrialBuildingBlocks.h>

using namespace mw;


class RandomizeBackground : public Action {
    
public:
    RandomizeBackground(shared_ptr<StimulusNode> backgroundNode);
    virtual bool execute();
    
private:
    shared_ptr<StimulusNode> backgroundNode;
    
};


#endif
