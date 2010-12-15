/*
 *  WhiteNoiseBackground.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include "WhiteNoiseBackground.h"

#include <MWorksCore/StandardVariables.h>


WhiteNoiseBackground::WhiteNoiseBackground(const std::string &tag,
                                           shared_ptr<Variable> anotherAttribute) :
    Stimulus(tag),
    anotherAttribute(anotherAttribute)
{ }


WhiteNoiseBackground::~WhiteNoiseBackground() { }


void WhiteNoiseBackground::load(shared_ptr<StimulusDisplay> display) {
    if (loaded)
        return;

    display->setCurrent(0);
    display->getCurrentViewportSize(width, height);

    pixels.resize(width * height);
    
    loaded = true;
}


void WhiteNoiseBackground::draw(shared_ptr<StimulusDisplay> display) {
    // If we're drawing to the main display, randomize the pixels
    if (display->getCurrentContextIndex() == 0) {
        randomizePixels();
    }

    glWindowPos2i(0, 0);
    glDrawPixels(width, height, GL_LUMINANCE, PIXEL_TYPE, &(pixels[0]));
}


Datum WhiteNoiseBackground::getCurrentAnnounceDrawData() {
    Datum announceData = Stimulus::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_TYPE, "white_noise_background");
    return announceData;
}


void WhiteNoiseBackground::randomizePixels() {
    boost::uniform_real<PixelType> randDist(0.0, 1.0);
    boost::variate_generator< boost::mt19937&, boost::uniform_real<PixelType> > randVar(randGen, randDist);
    
    for (size_t i = 0; i < pixels.size(); i++) {
        pixels[i] = randVar();
    }
}























