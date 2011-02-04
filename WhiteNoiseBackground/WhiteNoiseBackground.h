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
    WhiteNoiseBackground(const std::string &tag);

    virtual ~WhiteNoiseBackground();
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void unload(shared_ptr<StimulusDisplay> display);
    virtual void draw(shared_ptr<StimulusDisplay> display);
    virtual Datum getCurrentAnnounceDrawData();
    
    void randomizePixels();
    
private:
    WhiteNoiseBackground(const WhiteNoiseBackground &other);

    typedef std::pair<GLint, GLint> DisplayDimensions;
    std::map<int, DisplayDimensions> dims;

    static const GLint componentsPerPixel = 4;
    std::vector<GLuint> pixels;
    boost::mutex pixelsMutex;

    boost::rand48 randGen;
    boost::uniform_int<GLubyte> randDist;

};


#endif






















