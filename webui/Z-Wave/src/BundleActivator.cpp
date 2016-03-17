//
// BundleActivatior.cpp
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Exception.h"
#include "Poco/OSP/BundleContext.h"
#include "ZWayRequestHandler.h"


namespace IoT {
namespace Web {
namespace ZWave {


class BundleActivator : public Poco::OSP::BundleActivator
{
public:
	BundleActivator() = default;

	~BundleActivator() override = default;

	void start(Poco::OSP::BundleContext::Ptr /*bundleContext*/) override {}

	void stop(Poco::OSP::BundleContext::Ptr /*bundleContext*/) override {}
};


} } } // namespace IoT::Web::ZWave


POCO_BEGIN_NAMED_MANIFEST(WebServer, Poco::OSP::Web::WebRequestHandlerFactory)
	POCO_EXPORT_CLASS(IoT::Web::ZWave::ZWayRequestHandlerFactory)
POCO_END_MANIFEST


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Web::ZWave::BundleActivator)
POCO_END_MANIFEST
