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


WhiteNoiseBackground::WhiteNoiseBackground(const std::string &tag) :
    Stimulus(tag),
    randDist(randGen)
{ }


WhiteNoiseBackground::~WhiteNoiseBackground() { }


void WhiteNoiseBackground::load(shared_ptr<StimulusDisplay> display) {
    if (loaded)
        return;
    
    for (int i = 0; i < display->getNContexts(); i++) {
        display->setCurrent(i);

        GLint width, height;
        display->getCurrentViewportSize(width, height);
        dims[i] = DisplayDimensions(width, height);
        if (i == 0) {
            pixels.resize(width * height);
        }
    }
    
    loaded = true;
}


void WhiteNoiseBackground::draw(shared_ptr<StimulusDisplay> display) {
    DisplayDimensions &currentDims = dims[display->getCurrentContextIndex()];
    glWindowPos2i(0, 0);
    glDrawPixels(currentDims.first, currentDims.second, GL_LUMINANCE, PIXEL_TYPE, &(pixels[0]));
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























