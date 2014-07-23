//
//  CircularFixationPoint.h
//  CircleStimulusPlugin
//
//  Created by Christopher Stawarz on 7/23/14.
//
//

#ifndef __CircleStimulusPlugin__CircularFixationPoint__
#define __CircleStimulusPlugin__CircularFixationPoint__

#include "CircleStimulus.h"


BEGIN_NAMESPACE_MW


class CircularFixationPoint : public CircleStimulus, public CircularRegionTrigger, public GoldStandard {
    
public:
    static void describeComponent(ComponentInfo &info);
    
    explicit CircularFixationPoint(const ParameterValueMap &parameters);
    
    ExpandableList<Datum>* getGoldStandardValues() MW_OVERRIDE;
    Datum getCurrentAnnounceDrawData() MW_OVERRIDE;
    
};


END_NAMESPACE_MW


#endif /* !defined(__CircleStimulusPlugin__CircularFixationPoint__) */
