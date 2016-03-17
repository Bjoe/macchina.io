//
// ResetController.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_WEB_ZWAVE_COMMAND_RESETCONTROLLER_H
#define IOT_WEB_ZWAVE_COMMAND_RESETCONTROLLER_H


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


class ResetController : public Handler
{
public:
	ResetController();

	// Handler interface
public:
	Poco::JSON::Object handle(
		Poco::OSP::BundleContext::Ptr bundleContext,
		Poco::SharedPtr<Poco::Net::HTMLForm> /*form*/) const override;
};


} } } } // namespace IoT::Web::ZWave::Command


#endif // IOT_WEB_ZWAVE_COMMAND_RESETCONTROLLER_H
