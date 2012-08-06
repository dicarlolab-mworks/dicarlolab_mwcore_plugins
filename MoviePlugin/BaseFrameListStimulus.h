//
//  BaseFrameListStimulus.h
//  MovieStimulusPlugin
//
//  Created by Christopher Stawarz on 8/6/12.
//
//

#ifndef __MovieStimulusPlugin__BaseFrameListStimulus__
#define __MovieStimulusPlugin__BaseFrameListStimulus__

#include <MWorksCore/StandardDynamicStimulus.h>

using namespace mw;


class BaseFrameListStimulus : public StandardDynamicStimulus {
    
public:
    static const std::string ENDED;
    static const std::string LOOP;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit BaseFrameListStimulus(const ParameterValueMap &parameters);
    
    virtual void freeze(bool shouldFreeze = true);
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void unload(shared_ptr<StimulusDisplay> display);
    
    virtual void drawFrame(shared_ptr<StimulusDisplay> display);
    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual void startPlaying();
    
    int getFrameNumber();
    int getLastFrameDrawn() const { return lastFrameDrawn; }
    
    virtual int getNumFrames() = 0;
    virtual int getNominalFrameNumber() = 0;
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) = 0;
    
private:
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    
    int lastFrameDrawn;
    
};


#endif /* defined(__MovieStimulusPlugin__BaseFrameListStimulus__) */
