//
// NodesManager.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_NODESMANAGER_H
#define IOT_ZWAVE_NODESMANAGER_H


#include <map>

#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"

#include "Poco/Logger.h"
#include "Poco/SharedPtr.h"
#include "Poco/Timer.h"

#include "IoT/ZWave/Node.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Event.h"


namespace IoT {
namespace ZWave {


class NodesManager
{
public:
	using Ptr = Poco::SharedPtr<NodesManager>;

	NodesManager(
		Way::Controller::Ptr controller,
		Poco::OSP::BundleContext::Ptr bundleContext,
		Poco::Logger& log);

	void deviceAdded(Way::Event event);
	void deviceRemoved(Way::Event event);
	void instanceAdded(Way::Event event);
	void instanceRemoved(Way::Event event);
	void commandAdded(Way::Event event);
	void commandRemoved(Way::Event event);
	void unknown(Way::Event event);

	void removeAllNodes();

	void triggerTask(Poco::Timer& /*timer*/);

private:
	Way::Controller::Ptr controller_;
	Poco::OSP::BundleContext::Ptr bundleContext_;
	Poco::Logger& log_;

	std::map<Way::NodeIdentifier, Node*> nodes_ = {};
	std::map<Way::NodeIdentifier, Poco::OSP::ServiceRef::Ptr> serviceRefs_ = {};

	void registerNode(Way::NodeIdentifier id);
	bool isDeviceExists(Way::NodeIdentifier id);
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_NODESMANAGER_H
