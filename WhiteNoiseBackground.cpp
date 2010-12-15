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
}


void WhiteNoiseBackground::draw(shared_ptr<StimulusDisplay> display) {
}


Datum WhiteNoiseBackground::getCurrentAnnounceDrawData() {
    Datum announceData = Stimulus::getCurrentAnnounceDrawData();
	announceData.addElement(STIM_TYPE, "white_noise_background");
    return announceData;
}
