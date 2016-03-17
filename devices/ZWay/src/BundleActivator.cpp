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
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleContext.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;


namespace IoT {
namespace ZWave {
namespace Way {


class BundleActivator : public Poco::OSP::BundleActivator
{
public:
	BundleActivator() = default;

	~BundleActivator() final = default;

	void start(BundleContext::Ptr pContext) final
	{
		std::string msg("BundleActivator::start() for ");
		msg.append(pContext->thisBundle()->name());
		pContext->logger().information(msg);
	}

	void stop(BundleContext::Ptr pContext) final
	{
		std::string msg("BundleActivator::stop() for ");
		msg.append(pContext->thisBundle()->name());
		pContext->logger().information(msg);
	}
};


} } } // namespace IoT::ZWave::Way


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::ZWave::Way::BundleActivator)
POCO_END_MANIFEST
