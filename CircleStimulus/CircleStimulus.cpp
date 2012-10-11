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


void CircleStimulus::describeComponent(ComponentInfo &info) {
    PointStimulus::describeComponent(info);
    info.setSignature("stimulus/circle");
}


CircleStimulus::CircleStimulus(const ParameterValueMap &parameters) :
    PointStimulus(parameters)
{ }


#define TWO_PI (2.0 * M_PI)

void CircleStimulus::drawInUnitSquare(shared_ptr<StimulusDisplay> display) {
    
	// draw point at desired location with desired color
	// fill a (0,0) (1,1) box with the right color
    if(r == NULL || g == NULL || b == NULL ){
		merror(M_DISPLAY_MESSAGE_DOMAIN,
			   "NULL color variable in CircleStimulus.");
	}
	
	
    // get current values in these variables.
	GLfloat _r = (float)(*r);
	GLfloat _g = (float)(*g);
	GLfloat _b = (float)(*b);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(_r, _g, _b, *alpha_multiplier);
	
	// the number of sections depends on the size of the circle and the location of the screen
	// this needs to be revisted
	int sections = 10*std::max(xscale->getValue().getFloat(), yscale->getValue().getFloat());
	
	
	glVertex3f(0.5, 0.5, 0.0);
	
	for (int i=0; i<=sections; ++i)
	{
		glVertex3f(0.5 + (0.5 * cos(i * TWO_PI / sections)), 
				   0.5 + (0.5 * sin(i * TWO_PI / sections)),
				   0.0);		
	}
	glEnd();
	
	//mprintf("fixpoint r: %g, g: %g, b: %g", red, green, blue);
	
	//glColor3f(_r,_g,_b);
	//	glVertex3f(0.0,0.0,0.0);
	//	glVertex3f(1.0,0.0,0.0);
	//	glVertex3f(1.0,1.0,0.0);
	//	glVertex3f(0.0,1.0,0.0);
	//	
	//    glEnd();
    
	glDisable(GL_BLEND);
    
    last_r = _r;
    last_g = _g;
    last_b = _b;
    
	
}


Datum CircleStimulus::getCurrentAnnounceDrawData() {
    Datum announceData(PointStimulus::getCurrentAnnounceDrawData());
    announceData.addElement(STIM_TYPE, "circle");
    return announceData;
}




















