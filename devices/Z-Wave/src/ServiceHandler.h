//
// ServiceHandler.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DEVICES_SERVICEHANDLER_H
#define IOT_ZWAVE_DEVICES_SERVICEHANDLER_H


#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"
#include <map>
#include <string>


namespace IoT {
namespace ZWave {
namespace Devices {


class ServiceHandler
{
public:
	explicit ServiceHandler(Poco::OSP::BundleContext::Ptr context);

	void registerService(Poco::OSP::ServiceRef::ConstPtr& serviceRef);
	void unregisterService(Poco::OSP::ServiceRef::ConstPtr& serviceRef);

private:
	Poco::OSP::BundleContext::Ptr context_;
	std::map<const std::string, Poco::OSP::ServiceRef::Ptr> serviceRefs_ = {};
};


} } } // namespace IoT::ZWave::Devices


#endif // IOT_ZWAVE_DEVICES_SERVICEHANDLER_H
