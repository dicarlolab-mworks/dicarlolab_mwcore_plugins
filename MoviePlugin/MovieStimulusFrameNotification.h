/*
 *  MovieStimulusFrameNotification.h
 *  MWorksCore
 *
 *  Created by labuser on 5/23/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef MOVIE_STIMULUS_FRAME_NOTIFICATION_H_
#define MOVIE_STIMULUS_FRAME_NOTIFICATION_H_

#include "MovieStimulus.h"
#include "MWorksCore/GenericVariable.h"

class mMovieStimulus;

class mMovieStimulusFrameNotification : public VariableNotification {
protected:
	
	mMovieStimulus *movie_stimulus;
	
public:
	
	mMovieStimulusFrameNotification(mMovieStimulus *the_ms);
	virtual void notify(const Datum& data);
    virtual void notify(const Datum& data, MWorksTime timeUS);
	
};


#endif /* MOVIE_STIMULUS_FRAME_NOTIFICATION_H_ */
