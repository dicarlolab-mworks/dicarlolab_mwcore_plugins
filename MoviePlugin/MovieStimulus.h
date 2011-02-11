/*
 *  MovieStimulus.h
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef MOVIE_STIMULUS_H_
#define MOVIE_STIMULUS_H_

#include "MWorksCore/StandardDynamicStimulus.h"
#include "MWorksCore/ComponentRegistry.h"
using namespace mw;


class MovieStimulus : public StandardDynamicStimulus {
	
protected: 

	boost::shared_ptr<StimulusGroup> stimulus_group;
    shared_ptr<Variable> ended;
    shared_ptr<Variable> loop;
	
public:
	
	MovieStimulus(const std::string &_tag,
                  shared_ptr<Variable> _frames_per_second,
                  shared_ptr<StimulusGroup> _stimulus_group,
                  shared_ptr<Variable> ended,
                  shared_ptr<Variable> loop);
    
    virtual void load(shared_ptr<StimulusDisplay> display);
    virtual void unload(shared_ptr<StimulusDisplay> display);

	virtual int getFrameNumber();
    virtual bool needDraw();
    virtual void drawFrame(shared_ptr<StimulusDisplay> display, int frameNumber);
	virtual Datum getCurrentAnnounceDrawData();

};

class MovieStimulusFactory : public ComponentFactory {
	virtual boost::shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg);
};



#endif /* MOVIE_STIMULUS_H_ */






















