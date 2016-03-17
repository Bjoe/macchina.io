//
// Session.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_SESSION_H
#define IOT_ZWAVE_SESSION_H


#include "IoT/ZWave/Way/Event.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"

#include "Poco/OSP/BundleContext.h"

#include "Poco/Timer.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"

#include <string>
#include <functional>


namespace IoT {
namespace ZWave {
namespace Way {


class Session
{
public:
	static constexpr auto SYMBOLIC_NAME = "io.macchina.zwave";

	using Ptr = Poco::SharedPtr<Session>;

	static Session::Ptr createInstance(
			const Poco::OSP::BundleContext::Ptr& bundleContext,
			const std::string& instanceName,
			Poco::Logger& log);

	virtual ~Session();

	Controller::Ptr controller() const;

	Error start(std::function<void(Event)> deviceAddCallback);
	Error stop();

	Error error();

private:
	Session(Controller::Ptr controller, Poco::Logger& log, Error error);

	Controller::Ptr controller_;
	Poco::Logger& log_;
	Error error_;
	std::function<void()> terminatedCallback_ =
	[&] ()
	{
		  log_.information("ZWay is terminated !!!");
	};
};


} } } // namespace IoT::ZWave::Way


#endif // IOT_ZWAVE_SESSION_H
