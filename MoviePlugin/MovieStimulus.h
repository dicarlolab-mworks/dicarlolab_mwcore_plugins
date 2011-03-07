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
#include <MWorksCore/ComponentFactory.h>

using namespace mw;


class BaseMovieStimulus : public StandardDynamicStimulus {
    
public:
    BaseMovieStimulus(const std::string &tag,
                      shared_ptr<Variable> framesPerSecond,
                      shared_ptr<Variable> ended,
                      shared_ptr<Variable> loop);
    
    virtual ~BaseMovieStimulus() { }
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void unload(shared_ptr<StimulusDisplay> display);
    
    virtual int getFrameNumber();
    virtual bool needDraw();
    virtual void drawFrame(shared_ptr<StimulusDisplay> display, int frameNumber);
    virtual Datum getCurrentAnnounceDrawData();

protected:
    virtual int getNumFrames() = 0;
    virtual shared_ptr<Stimulus> getStimulusForFrame(int frameNumber) = 0;
    
private:
    BaseMovieStimulus(const BaseMovieStimulus &other);

    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
    
};


class MovieStimulus : public BaseMovieStimulus {
    
public:
    MovieStimulus(const std::string &tag,
                  shared_ptr<Variable> framesPerSecond,
                  shared_ptr<StimulusGroup> stimulusGroup,
                  shared_ptr<Variable> ended,
                  shared_ptr<Variable> loop);
    
    virtual ~MovieStimulus() { }

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


class MovieStimulusFactory : public ComponentFactory {
    virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
                                                   ComponentRegistry *reg);
};


#endif /* MOVIE_STIMULUS_H_ */






















