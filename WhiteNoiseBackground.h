/*
 *  WhiteNoiseBackground.h
 *  WhiteNoiseBackground
 *
 *  Created by Christopher Stawarz on 12/15/10.
 *  Copyright 2010 MIT. All rights reserved.
 *
 */

#ifndef WhiteNoiseBackground_H_
#define WhiteNoiseBackground_H_

#include <MWorksCore/Component.h>
#include <MWorksCore/GenericVariable.h>

using namespace mw;


class WhiteNoiseBackground : public mw::Component {

public:
    WhiteNoiseBackground(const std::string &tag, shared_ptr<Variable> anotherAttribute);

    virtual ~WhiteNoiseBackground();
    
private:
    WhiteNoiseBackground(const WhiteNoiseBackground &other);
    
    shared_ptr<Variable> anotherAttribute;

};


#endif
