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
    anotherAttribute(anotherAttribute),
    randDist(randGen)
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
    glWindowPos2i(0, 0);
    glDrawPixels(width, height, GL_LUMINANCE, PIXEL_TYPE, &(pixels[0]));
}


Datum WhiteNoiseBackground::getCurrentAnnounceDrawData() {
    Datum announceData = Stimulus::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_TYPE, "white_noise_background");
    return announceData;
}


void WhiteNoiseBackground::randomizePixels() {
    for (size_t i = 0; i < pixels.size(); i++) {
        pixels[i] = randDist();
    }
}























