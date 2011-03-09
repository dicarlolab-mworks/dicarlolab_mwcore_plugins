/*
 *  MovieStimulusFactory.h
 *  MovieStimulus
 *
 *  Created by Christopher Stawarz on 3/9/11.
 *  Copyright 2011 MIT. All rights reserved.
 *
 */

#ifndef MovieStimulus_FACTORY_H
#define MovieStimulus_FACTORY_H

#include <MWorksCore/ComponentFactory.h>

using namespace mw;


class BaseMovieStimulusFactory : public ComponentFactory {
    
protected:
    void getBaseMovieParameters(std::map<std::string, std::string> &parameters,
                                ComponentRegistry *reg,
                                std::string &tag,
                                shared_ptr<Variable> &framesPerSecond,
                                shared_ptr<Variable> &ended,
                                shared_ptr<Variable> &loop);
    
};


class MovieStimulusFactory : public BaseMovieStimulusFactory {
    virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
                                                   ComponentRegistry *reg);
};


class ImageDirectoryMovieStimulusFactory : public BaseMovieStimulusFactory {
    virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
                                                   ComponentRegistry *reg);
};


#endif
