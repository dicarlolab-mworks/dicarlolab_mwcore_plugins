/*
 *  MovieStimulus.h
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef MOVIE_STIMULUS_H_
#define MOVIE_STIMULUS_H_

#include <MWorksCore/StandardDynamicStimulus.h>

using namespace mw;


class BaseMovieStimulus : public StandardDynamicStimulus {
    
public:
    static const std::string FRAMES_PER_SECOND;
    static const std::string ENDED;
    static const std::string LOOP;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit BaseMovieStimulus(const ParameterValueMap &parameters);
    
    virtual void freeze(bool shouldFreeze = true);
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void unload(shared_ptr<StimulusDisplay> display);
    
    virtual bool needDraw();
    virtual void drawFrame(shared_ptr<StimulusDisplay> display);
    virtual Datum getCurrentAnnounceDrawData();

protected:
    virtual void startPlaying();
    
    virtual int getFrameNumber();
    virtual int getNumFrames() = 0;
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) = 0;
    
private:
    shared_ptr<Variable> framesPerSecond;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    
    double framesPerUS;
    int lastFrameDrawn;
    
};


class MovieStimulus : public BaseMovieStimulus {
    
public:
    static const std::string STIMULUS_GROUP;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit MovieStimulus(const ParameterValueMap &parameters);

    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual int getNumFrames() {
        return stimulusGroup->getNElements();
    }

    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) {
        return stimulusGroup->getElement(frameNumber);
    }
    
private:
    shared_ptr<StimulusGroup> stimulusGroup;
    
};


class ImageDirectoryMovieStimulus : public BaseMovieStimulus {
    
public:
    static const std::string DIRECTORY_PATH;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit ImageDirectoryMovieStimulus(const ParameterValueMap &parameters);
    
    virtual Datum getCurrentAnnounceDrawData();
    
protected:
    virtual int getNumFrames() {
        return images.size();
    }
    
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) {
        return images[frameNumber];
    }
    
private:
    const std::string directoryPath;
    std::vector< shared_ptr<Stimulus> > images;
    
};


#endif /* MOVIE_STIMULUS_H_ */






















