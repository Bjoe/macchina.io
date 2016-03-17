//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include <map>
#include <string>

#include "Poco/ClassLibrary.h"
#include "Poco/Delegate.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"

#include "Poco/SharedPtr.h"

#include "IoT/ZWave/Node.h"

#include "ServiceHandler.h"


namespace IoT {
namespace ZWave {
namespace Devices {


class BundleActivator : public Poco::OSP::BundleActivator
{
	// BundleActivator interface
public:
	BundleActivator() = default;

	~BundleActivator() final = default;

	void start(Poco::OSP::BundleContext::Ptr pContext) final
	{
		serviceHandler_ = new ServiceHandler(pContext);

		std::vector<Poco::OSP::ServiceRef::Ptr> services;
		pContext->registry().find(R"(name =~ ")" + std::string(IoT::ZWave::Node::SYMBOLIC_NAME) + R"(#*")", services);

		for (Poco::OSP::ServiceRef::ConstPtr& service : services)
		{
			serviceHandler_->registerService(service);
		}

		Poco::OSP::ServiceRegistry& registry = pContext->registry();
		registry.serviceRegistered += Poco::delegate(this, &BundleActivator::onRegisterUnregisterEvent);
		registry.serviceUnregistered += Poco::delegate(this, &BundleActivator::onRegisterUnregisterEvent);
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext) final
	{
		Poco::OSP::ServiceRegistry& registry = pContext->registry();
		registry.serviceRegistered -= Poco::delegate(this, &BundleActivator::onRegisterUnregisterEvent);
		registry.serviceUnregistered -= Poco::delegate(this, &BundleActivator::onRegisterUnregisterEvent);

		delete serviceHandler_;
	}

	void onRegisterUnregisterEvent(const void* /*sender*/, Poco::OSP::ServiceEvent& event)
	{
		Poco::OSP::ServiceRef::ConstPtr serviceRef = event.service();
		const std::string serviceName = serviceRef->name();

		if (std::string(IoT::ZWave::Node::SYMBOLIC_NAME).compare(serviceName) <= 0)
		{
			if (Poco::OSP::ServiceEvent::EV_SERVICE_REGISTERED == event.what())
			{
				serviceHandler_->registerService(serviceRef);
			}
			else
			{
				serviceHandler_->unregisterService(serviceRef);
			}
		}
	}

private:
	ServiceHandler* serviceHandler_ = nullptr;
};


} } } // namespace IoT::ZWave::Devices


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
POCO_EXPORT_CLASS(IoT::ZWave::Devices::BundleActivator)
POCO_END_MANIFEST
