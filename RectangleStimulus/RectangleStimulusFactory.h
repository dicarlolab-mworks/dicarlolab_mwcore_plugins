/*
 *  RectangleStimulusFactory.h
 *  MWorksCore
 *
 *  Created by bkennedy on 8/26/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */


#ifndef RECTANGLE_STIMULUS_FACTORY_H
#define RECTANGLE_STIMULUS_FACTORY_H

#include "MWorksCore/ComponentFactory.h"
using namespace mw;

class mRectangleStimulusFactory : public ComponentFactory {
	virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
												ComponentRegistry *reg);
};

#endif
