/*
 *  WhiteNoiseBackground.cpp
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#include "WhiteNoiseBackground.h"


WhiteNoiseBackground::WhiteNoiseBackground(const std::string &tag,
                                                             shared_ptr<Variable> anotherAttribute) :
    mw::Component(tag),
    anotherAttribute(anotherAttribute)
{ }


WhiteNoiseBackground::~WhiteNoiseBackground() { }
