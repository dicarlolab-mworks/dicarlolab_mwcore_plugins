//
//  CircularFixationPoint.cpp
//  CircleStimulusPlugin
//
//  Created by Christopher Stawarz on 7/23/14.
//
//

#include "CircularFixationPoint.h"


BEGIN_NAMESPACE_MW


void CircularFixationPoint::describeComponent(ComponentInfo &info) {
    CircleStimulus::describeComponent(info);
    info.setSignature("stimulus/circular_fixation_point");
    info.addParameter(FixationPoint::TRIGGER_WIDTH);
    info.addParameter(FixationPoint::TRIGGER_WATCH_X);
    info.addParameter(FixationPoint::TRIGGER_WATCH_Y);
    info.addParameter(FixationPoint::TRIGGER_FLAG);
}


CircularFixationPoint::CircularFixationPoint(const ParameterValueMap &parameters):
    CircleStimulus(parameters),
    CircularRegionTrigger(registerVariable(parameters[X_POSITION]),
                          registerVariable(parameters[Y_POSITION]),
                          registerVariable(parameters[FixationPoint::TRIGGER_WIDTH]),
                          VariablePtr(parameters[FixationPoint::TRIGGER_WATCH_X]),
                          VariablePtr(parameters[FixationPoint::TRIGGER_WATCH_Y]),
                          VariablePtr(parameters[FixationPoint::TRIGGER_FLAG]))
{ }


ExpandableList<Datum>* CircularFixationPoint::getGoldStandardValues() {
    goldStandardValues->clear();
    
    Datum h_loc = xoffset->getValue();
    goldStandardValues->addElement(h_loc);
    
    Datum v_loc = yoffset->getValue();
    goldStandardValues->addElement(v_loc);
    
    return goldStandardValues;
}


Datum CircularFixationPoint::getCurrentAnnounceDrawData() {
    Datum announceData(CircleStimulus::getCurrentAnnounceDrawData());
    
    announceData.addElement(STIM_TYPE, "circular_fixation_point");
    
    // CircularRegionTrigger parameters
    announceData.addElement("center_x", centerx->getValue().getFloat());
    announceData.addElement("center_y", centery->getValue().getFloat());
    announceData.addElement("width", width->getValue().getFloat());
    
    return announceData;
}


END_NAMESPACE_MW


























