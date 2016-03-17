//
// ServiceState.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_WEB_ZWAVE_COMMAND_SERVICESTATE_HPP
#define IOT_WEB_ZWAVE_COMMAND_SERVICESTATE_HPP


#include <string>

#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/OSP/BundleContext.h"

#include "Handler.h"


namespace IoT {
namespace Web {
namespace ZWave {
namespace Command {


class ServiceState : public Handler
{
public:
	ServiceState();

	// Handler interface
	Poco::JSON::Object handle(
		Poco::OSP::BundleContext::Ptr bundleContext,
		Poco::SharedPtr<Poco::Net::HTMLForm> /*form*/) const override;
};


} } } } // namespace IoT::ZWave::Web::Command


#endif // IOT_WEB_ZWAVE_COMMAND_SERVICESTATE_HPP
