/*
 *  FakeMonkey.h
 *  MonkeyWorksCore
 *
 *  Created by David Cox on 6/13/05.
 *  Copyright 2005 MIT. All rights reserved.
 *
 */
#ifndef	FAKE_MONKEY_H_
#define	FAKE_MONKEY_H_

#include "MonkeyWorksCore/IODevice.h"
#include "MonkeyWorksCore/ComponentFactory.h"
#include "FakeMonkeyEyeMovementChannel.h"
#include "boost/random.hpp"
#include "boost/enable_shared_from_this.hpp"
using namespace mw;

#define FAKE_MONKEY_MEAN_FIXATION_DURATION_US 200*1000
#define FAKE_MONKEY_MEAN_SACCADE_DURATION_US 50*1000
#define FAKE_MONKEY_MEAN_SPIKING_RATE 30.0

class mFakeMonkey : public IODevice {

protected:

	shared_ptr<boost::mutex> monkey_lock;

	shared_ptr <mFakeMonkeyStatus> status;	
	shared_ptr<float> saccade_start_h, saccade_start_v;
	shared_ptr<float> saccade_target_h, saccade_target_v;
	shared_ptr<MonkeyWorksTime> saccade_start_time;
	bool command_pending;
	double saccade_next_target_h, saccade_next_target_v;
	shared_ptr<ScheduleTask> movement_node;
	
	shared_ptr<MonkeyWorksTime> saccade_duration;
	MonkeyWorksTime fixation_duration;
	
	shared_ptr<Scheduler> scheduler;
	
	shared_ptr <Variable> spike_rate;
	shared_ptr<ScheduleTask> spike_node;
	boost::mt19937 rng;
		
	std::vector<boost::shared_ptr<mFakeMonkeyEyeMovementChannel> > movement_channels;
	std::vector<boost::shared_ptr<Variable> > spike_variables;
	
public:

	mFakeMonkey(const shared_ptr<Scheduler> &a_scheduler,
				const shared_ptr<Variable> &spike_rate_);
	//mFakeMonkey(const mFakeMonkey& copy);
	~mFakeMonkey();
	
	virtual bool attachPhysicalDevice();
	virtual bool initializeChannels();
	virtual bool startDeviceIO();
	virtual bool stopDeviceIO();
	virtual bool updateChannel(int index);
	virtual bool shutdown();
	
	void addChild(std::map<std::string, std::string> parameters,
				  mwComponentRegistry *reg,
				  shared_ptr<mw::Component> child);
	
	void startSaccading();
	void startFixating();
	void spike();
	
	void saccadeTo(const double x, 
				   const double y, 
				   const MonkeyWorksTime time_to_fixate_at_end_of_saccade);
	void fixate(const MonkeyWorksTime duration);
	
	shared_ptr<mFakeMonkey> shared_from_this() { return static_pointer_cast<mFakeMonkey>(IODevice::shared_from_this()); }
};



#endif

