/*
 *  WhiteNoiseBackground.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include "WhiteNoiseBackground.h"

#include <algorithm>

#include <MWorksCore/StandardVariables.h>


WhiteNoiseBackground::WhiteNoiseBackground(const std::string &tag) :
    Stimulus(tag),
    randDist(randGen)
{ }


WhiteNoiseBackground::~WhiteNoiseBackground() { }


void WhiteNoiseBackground::load(shared_ptr<StimulusDisplay> display) {
    if (loaded)
        return;

    GLint maxWidth = 0;
    GLint maxHeight = 0;
    
    for (int i = 0; i < display->getNContexts(); i++) {
        display->setCurrent(i);

        GLint width, height;
        display->getCurrentViewportSize(width, height);
        dims[i] = DisplayDimensions(width, height);
        
        maxWidth = std::max(width, maxWidth);
        maxHeight = std::max(height, maxHeight);
    }

    pixels.resize(maxWidth * maxHeight * componentsPerPixel);
    
    loaded = true;
}


void WhiteNoiseBackground::unload(shared_ptr<StimulusDisplay> display) {
    if (!loaded)
        return;
    
    dims.clear();
    pixels.clear();
    
    loaded = false;
}


void WhiteNoiseBackground::draw(shared_ptr<StimulusDisplay> display) {
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);

    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    DisplayDimensions &currentDims = dims[display->getCurrentContextIndex()];
    glWindowPos2i(0, 0);
    
    {
        boost::mutex::scoped_lock lock(pixelsMutex);
        glDrawPixels(currentDims.first, currentDims.second, pixelFormatCode, pixelTypeCode, &(pixels[0]));
    }

    glPopClientAttrib();
}


Datum WhiteNoiseBackground::getCurrentAnnounceDrawData() {
    Datum announceData = Stimulus::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_TYPE, "white_noise_background");
    return announceData;
}


void WhiteNoiseBackground::randomizePixels() {
    boost::mutex::scoped_lock lock(pixelsMutex);

    for (size_t i = 0; i < pixels.size(); i++) {
        PixelType randVal = randDist();
        for (size_t j = 0; j < componentsPerPixel - 1; j++) {
            pixels[i] = randVal;
            i++;
        }
        pixels[i] = randDist.max();
    }
}























