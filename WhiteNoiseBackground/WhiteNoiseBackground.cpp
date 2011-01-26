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
        
        glGenBuffers(1, &(buffers[i]));
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[i]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER,
                     (width * height * sizeof(PixelType) * componentsPerPixel),
                     NULL,
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
    
    loaded = true;
}


void WhiteNoiseBackground::unload(shared_ptr<StimulusDisplay> display) {
    if (!loaded)
        return;
    
    for (int i = 0; i < display->getNContexts(); i++) {
        display->setCurrent(i);
        glDeleteBuffers(1, &(buffers[i]));
    }
    
    dims.clear();
    buffers.clear();
    
    loaded = false;
}


void WhiteNoiseBackground::draw(shared_ptr<StimulusDisplay> display) {
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);

    // Set all pixel unpack parameters to default values
    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    int index = display->getCurrentContextIndex();
    DisplayDimensions &currentDims = dims[index];
    glWindowPos2i(0, 0);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[index]);
    glDrawPixels(currentDims.first, currentDims.second, PIXEL_FORMAT, PIXEL_TYPE, (GLvoid *)0);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    glPopClientAttrib();
}


Datum WhiteNoiseBackground::getCurrentAnnounceDrawData() {
    Datum announceData = Stimulus::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_TYPE, "white_noise_background");
    return announceData;
}


void WhiteNoiseBackground::randomizePixels() {
    shared_ptr<StimulusDisplay> display(StimulusDisplay::getCurrentStimulusDisplay());

    for (int i = 0; i < display->getNContexts(); i++) {
        display->setCurrent(i);
        DisplayDimensions &currentDims = dims[i];

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffers[i]);
        PixelType *pixels = (PixelType *)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);

        for (size_t i = 0; i < (currentDims.first * currentDims.second * componentsPerPixel); i++) {
            PixelType randVal = randDist();
            for (size_t j = 0; j < componentsPerPixel - 1; j++) {
                pixels[i] = randVal;
                i++;
            }
            pixels[i] = 1.0;
        }
        
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    }
}























