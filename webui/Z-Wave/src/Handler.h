//
// Handler.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_WEB_ZWAVE_COMMAND_HANDLER_H
#define IOT_WEB_ZWAVE_COMMAND_HANDLER_H


#include "Poco/Net/HTMLForm.h"
#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"

#include "Poco/OSP/BundleContext.h"


namespace IoT {
namespace Web {
namespace ZWave {
namespace Command {


class Handler
{
public:
	using Ptr = Poco::SharedPtr<Handler>;
	Handler() = default;
	virtual ~Handler() = default;

	virtual Poco::JSON::Object handle(
		Poco::OSP::BundleContext::Ptr bundleContext,
		Poco::SharedPtr<Poco::Net::HTMLForm> form) const = 0;
};


} } } } // namespace IoT::Web::ZWave::Command


#endif // IOT_WEB_ZWAVE_COMMAND_HANDLER_H
