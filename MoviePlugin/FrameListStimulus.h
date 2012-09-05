//
//  FrameListStimulus.h
//  MovieStimulusPlugin
//
//  Created by Christopher Stawarz on 8/6/12.
//
//

#ifndef __MovieStimulusPlugin__FrameListStimulus__
#define __MovieStimulusPlugin__FrameListStimulus__

#include "BaseFrameListStimulus.h"


class FrameListStimulus : public BaseFrameListStimulus {
    
public:
    static const std::string STIMULUS_GROUP;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit FrameListStimulus(const ParameterValueMap &parameters);
    
    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual void startPlaying();
    
    virtual int getNumFrames() {
        return stimulusGroup->getNElements();
    }
    
    virtual int getNominalFrameNumber();
    
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) {
        return stimulusGroup->getElement(frameNumber);
    }
    
private:
    shared_ptr<StimulusGroup> stimulusGroup;
    
    MWTime currentFrameTime;
    
};


#endif /* defined(__MovieStimulusPlugin__FrameListStimulus__) */
