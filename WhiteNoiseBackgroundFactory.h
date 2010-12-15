/*
 *  WhiteNoiseBackgroundFactory.h
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#ifndef WhiteNoiseBackground_FACTORY_H
#define WhiteNoiseBackground_FACTORY_H

#include <MWorksCore/ComponentFactory.h>

using namespace mw;


class WhiteNoiseBackgroundFactory : public ComponentFactory {
	virtual shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
                                                   ComponentRegistry *reg);
};


#endif
