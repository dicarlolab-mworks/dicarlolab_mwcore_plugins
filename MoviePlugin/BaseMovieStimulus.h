//
//  BaseMovieStimulus.h
//  MovieStimulusPlugin
//
//  Created by Christopher Stawarz on 8/6/12.
//
//

#ifndef __MovieStimulusPlugin__BaseMovieStimulus__
#define __MovieStimulusPlugin__BaseMovieStimulus__

#include "BaseFrameListStimulus.h"


class BaseMovieStimulus : public BaseFrameListStimulus {
    
public:
    static const std::string FRAMES_PER_SECOND;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit BaseMovieStimulus(const ParameterValueMap &parameters);
    
    virtual bool needDraw();
    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual void startPlaying();
    
    virtual int getNominalFrameNumber() { return int(double(getElapsedTime()) * framesPerUS); }
    
private:
    shared_ptr<Variable> framesPerSecond;
    
    double framesPerUS;
    
};


#endif /* defined(__MovieStimulusPlugin__BaseMovieStimulus__) */
