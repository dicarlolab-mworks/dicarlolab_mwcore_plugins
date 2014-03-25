/*
 *  CircleStimulus.h
 *  MWorksCore
 *
 *  Created by bkennedy on 8/26/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef CIRCLE_STIMULUS_H
#define CIRCLE_STIMULUS_H

#include <MWorksCore/ParameterValue.h>
#include <MWorksCore/StandardStimuli.h>

using namespace mw;


class CircleStimulus : public RectangleStimulus {

public:
    static void describeComponent(ComponentInfo &info);
    
    explicit CircleStimulus(const ParameterValueMap &parameters);
    
	virtual void drawInUnitSquare(shared_ptr<StimulusDisplay> display);
    virtual Datum getCurrentAnnounceDrawData();

};


#endif 
