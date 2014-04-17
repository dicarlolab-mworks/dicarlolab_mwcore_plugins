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


BEGIN_NAMESPACE_MW


class CircleStimulus : public RectangleStimulus {

public:
    static void describeComponent(ComponentInfo &info);
    
    explicit CircleStimulus(const ParameterValueMap &parameters);
    
    void load(shared_ptr<StimulusDisplay> display) MW_OVERRIDE;
    void drawInUnitSquare(shared_ptr<StimulusDisplay> display) MW_OVERRIDE;
    Datum getCurrentAnnounceDrawData() MW_OVERRIDE;
    
private:
    std::vector<double> pixelDensity;

};


END_NAMESPACE_MW


#endif 
