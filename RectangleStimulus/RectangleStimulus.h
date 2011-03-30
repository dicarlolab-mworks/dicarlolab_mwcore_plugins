/*
 *  RectangleStimulus.h
 *  MWorksCore
 *
 *  Created by bkennedy on 8/26/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef RECTANGLE_STIMULUS_H
#define RECTANGLE_STIMULUS_H

#include <MWorksCore/ParameterValue.h>
#include <MWorksCore/StandardStimuli.h>

using namespace mw;


class RectangleStimulus : public PointStimulus {

public:
    static void describeComponent(ComponentInfo &info);
    
    explicit RectangleStimulus(const ParameterValueMap &parameters);
    
	virtual Datum getCurrentAnnounceDrawData();

};


#endif 
