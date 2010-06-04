/*
 *  MovieFrame.cpp
 *  MWorksCore
 *
 *  Created by labuser on 5/16/08.
 *  Copyright 2008 MIT. All rights reserved.
 *
 */
#include "MovieFrame.h"
using namespace mw;


MovieFrame::MovieFrame(const shared_ptr<StimulusNode> frame, 
						 const MWorksTime next_frame_time) : 
frame_node(frame),
next_frame_at(next_frame_time)
{}

shared_ptr<StimulusNode> MovieFrame::stimNode() {
	return frame_node;
}

MWorksTime MovieFrame::nextFrameTime() const {
	return next_frame_at;
}


