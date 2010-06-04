/*
 *  MovieFrame.h
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */

#ifndef MOVIE_FRAME_H_
#define MOVIE_FRAME_H_

#include "MWorksCore/StimulusNode.h"
using namespace mw;

class MovieFrame {
private:
	shared_ptr <StimulusNode> frame_node;
	MWorksTime next_frame_at;
	std::string stim_tag;
public:
	MovieFrame(const shared_ptr<StimulusNode> frame, 
				const MWorksTime next_frame_time);
	shared_ptr<StimulusNode> stimNode();
	MWorksTime nextFrameTime() const;
};



#endif /* MOVIE_FRAME */


