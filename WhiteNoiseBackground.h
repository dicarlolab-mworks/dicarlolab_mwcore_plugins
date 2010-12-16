/*
 *  WhiteNoiseBackground.h
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#ifndef WhiteNoiseBackground_H_
#define WhiteNoiseBackground_H_

#include <boost/random.hpp>

#include <MWorksCore/Stimulus.h>

using namespace mw;


class WhiteNoiseBackground : public Stimulus {

public:
    WhiteNoiseBackground(const std::string &tag, shared_ptr<Variable> anotherAttribute);

    virtual ~WhiteNoiseBackground();
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void draw(shared_ptr<StimulusDisplay> display);
    virtual Datum getCurrentAnnounceDrawData();
    
private:
    WhiteNoiseBackground(const WhiteNoiseBackground &other);
    
    void randomizePixels();
    
    shared_ptr<Variable> anotherAttribute;

    GLint width, height;
#define PIXEL_TYPE GL_FLOAT
    typedef GLfloat PixelType;
    std::vector<PixelType> pixels;

    boost::mt19937 randGen;
    boost::uniform_01< boost::mt19937&, PixelType > randDist;

};


#endif
