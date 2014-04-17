/*
 *  CircleStimulus.cpp
 *  MWorksCore
 *
 *  Created by bkennedy on 8/26/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */


#include <cmath>

#include "CircleStimulus.h"


BEGIN_NAMESPACE_MW


void CircleStimulus::describeComponent(ComponentInfo &info) {
    RectangleStimulus::describeComponent(info);
    info.setSignature("stimulus/circle");
}


CircleStimulus::CircleStimulus(const ParameterValueMap &parameters) :
    RectangleStimulus(parameters)
{ }


void CircleStimulus::load(shared_ptr<StimulusDisplay> display) {
    if (loaded)
        return;
    
    pixelDensity.clear();
    
    GLdouble xMin, xMax, yMin, yMax;
    GLint width, height;
    
    display->getDisplayBounds(xMin, xMax, yMin, yMax);
    
    for (int i = 0; i < display->getNContexts(); i++) {
        OpenGLContextLock ctxLock = display->setCurrent(i);
        display->getCurrentViewportSize(width, height);
        pixelDensity.push_back(double(width) / (xMax - xMin));
    }
    
    loaded = true;
}


#define TWO_PI (2.0 * M_PI)

void CircleStimulus::drawInUnitSquare(shared_ptr<StimulusDisplay> display) {
    // get current values in these variables.
	GLfloat _r = (float)(*r);
	GLfloat _g = (float)(*g);
	GLfloat _b = (float)(*b);
	GLfloat _a = (float)(*alpha_multiplier);
	
	glColor4f(_r, _g, _b, _a);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// The formula for the number of sections is borrowed from http://slabode.exofire.net/circle_draw.shtml
    double radius = std::max(xscale->getValue().getFloat(), yscale->getValue().getFloat()) / 2.0;
	int sections = 10 * std::sqrt(radius * pixelDensity.at(display->getCurrentContextIndex()));
	
	glBegin(GL_TRIANGLE_FAN);
    
	glVertex2f(0.5, 0.5);
	
	for (int i=0; i<=sections; ++i)
	{
		glVertex2f(0.5 + (0.5 * std::cos(i * TWO_PI / sections)),
				   0.5 + (0.5 * std::sin(i * TWO_PI / sections)));
	}
    
	glEnd();
    
	glDisable(GL_BLEND);
    
    last_r = _r;
    last_g = _g;
    last_b = _b;
    last_alpha = _a;
}


Datum CircleStimulus::getCurrentAnnounceDrawData() {
    Datum announceData(RectangleStimulus::getCurrentAnnounceDrawData());
    announceData.addElement(STIM_TYPE, "circle");
    return announceData;
}


END_NAMESPACE_MW




















