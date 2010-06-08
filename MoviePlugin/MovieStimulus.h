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

#include "MWorksCore/DynamicStimulusDriver.h"
#include "MWorksCore/Stimulus.h"
#include "MWorksCore/ComponentRegistry.h"
using namespace mw;


class MovieStimulus : public DynamicStimulusDriver, public Stimulus {
	
protected: 

	boost::shared_ptr<StimulusGroup> stimulus_group;
	
public:
	
	MovieStimulus(const std::string &_tag,
                  const boost::shared_ptr<Scheduler> &_scheduler,
                  const boost::shared_ptr<StimulusDisplay> &_display,
                  const boost::shared_ptr<Variable> &_frames_per_second,
                  const boost::shared_ptr<Variable> &_statistics_reporting,
                  const boost::shared_ptr<Variable> &_error_reporting,
                  const boost::shared_ptr<StimulusGroup> &_stimulus_group);
	
	virtual void draw(shared_ptr<StimulusDisplay> display);
	virtual Datum getCurrentAnnounceDrawData();

};

class MovieStimulusFactory : public ComponentFactory {
	virtual boost::shared_ptr<mw::Component> createObject(std::map<std::string, std::string> parameters,
													   ComponentRegistry *reg);
};



#endif /* MOVIE_STIMULUS_H_ */

