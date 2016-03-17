//
// ZWayRequestHandler.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_WEB_ZWAVE_ZWAYREQUESTHANDLER_H
#define IOT_WEB_ZWAVE_ZWAYREQUESTHANDLER_H


#include <map>
#include <string>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/Web/WebRequestHandlerFactory.h"

#include "Exclusion.h"
#include "Handler.h"
#include "Inclusion.h"
#include "ResetController.h"
#include "ServiceState.h"
#include "ShowNodes.h"


namespace IoT {
namespace Web {
namespace ZWave {


class ZWayRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	explicit ZWayRequestHandler(Poco::OSP::BundleContext::Ptr bundleContext);

	// HTTPRequestHandler interface
	void handleRequest(
		Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response) final;
	std::string handleCommand(
		std::string command,
		Poco::OSP::ServiceRef::Ptr serviceRef);

private:
	Poco::OSP::BundleContext::Ptr bundleContext_;
	std::map<const std::string, const IoT::Web::ZWave::Command::Handler::Ptr> commandHandlers_ = {
		{"startInclusion", new Command::Inclusion()},
		{"stopInclusion", new Command::Inclusion()},
		{"startExclusion", new Command::Exclusion()},
		{"stopExclusion", new Command::Exclusion()},
		{"showNodes", new Command::ShowNodes()},
		{"state", new Command::ServiceState()},
		{"resetData", new Command::ResetController()},
	};

	void sendErrorResponse(Poco::Net::HTTPServerResponse& response,
		Poco::Net::HTTPResponse::HTTPStatus status);
};

class ZWayRequestHandlerFactory
	: public Poco::OSP::Web::WebRequestHandlerFactory
{
	// HTTPRequestHandlerFactory interface
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(
		const Poco::Net::HTTPServerRequest& request) final;
};


} } } // namespace IoT::Web::ZWave


#endif // IOT_WEB_ZWAVE_ZWAYREQUESTHANDLER_H
