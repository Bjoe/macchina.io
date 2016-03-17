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


#include <string>
#include <functional>

#include "Poco/ClassLibrary.h"
#include "Poco/SharedPtr.h"
#include "Poco/Tuple.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/Timer.h"

#include "IoT/ZWave/Way/Error.h"
#include "IoT/ZWave/Way/Session.h"
#include "IoT/ZWave/NodesManager.h"
#include "IoT/ZWave/Service.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;


namespace IoT {
namespace ZWave {


class BundleActivator : public Poco::OSP::BundleActivator
{
public:
	BundleActivator() = default;

	~BundleActivator() override = default;

	void createZwave(BundleContext::Ptr bundleContext)
	{
		Poco::Logger& log = bundleContext->logger();
		std::string symbolicName(Way::Session::SYMBOLIC_NAME);
		zwaveSession_ = Way::Session::createInstance(bundleContext, symbolicName, log);
		Way::Error zWayError = zwaveSession_->error();
		if (zWayError.isNoError())
		{
			Way::Controller::Ptr controller = zwaveSession_->controller();
			nodesServiceRegisterHandler_ = new NodesManager(controller, bundleContext, log);
			zWayError = zwaveSession_->start(callback_);
			if (zWayError.isNoError())
			{
				Properties properties;
				Service::Ptr service = new Service(controller, nodesServiceRegisterHandler_);
				serviceRef_ = bundleContext->registry().registerService(
					Service::SERVICE_NAME,
					service,
					properties);
				log.information("ZWave service is registered in OSGi");
			}
			else
			{
				log.error(zWayError.errorMessage());
			}
		}
		else
		{
			log.error(zWayError.errorMessage());
		}
	}

	void start(BundleContext::Ptr bundleContext) final
	{
		bundleContext_ = bundleContext;
		Poco::Logger& log = bundleContext->logger();
		std::string msg("BundleActivator::start() for ");
		msg.append(bundleContext->thisBundle()->name());
		log.information(msg);

		createZwave(bundleContext);

		timer_.start(Poco::TimerCallback<NodesManager>(*nodesServiceRegisterHandler_, &NodesManager::triggerTask));
	}

	void stop(BundleContext::Ptr bundleContext) final
	{
		std::string msg("BundleActivator::stop() for ");
		msg.append(bundleContext->thisBundle()->name());
		bundleContext->logger().information(msg);
		timer_.stop();

		if (!serviceRef_.isNull())
		{
			bundleContext->registry().unregisterService(serviceRef_);
			serviceRef_ = nullptr;
		}

		if (!zwaveSession_.isNull())
		{
			zwaveSession_->stop();
			if(nodesServiceRegisterHandler_)
			{
				nodesServiceRegisterHandler_->removeAllNodes();
				nodesServiceRegisterHandler_ = nullptr;
			}
			zwaveSession_ = nullptr;
		}
		bundleContext_ = nullptr;
	}

private:
	Poco::Timer timer_ = {1000, 5000};
	BundleContext::Ptr bundleContext_ = nullptr;
	Way::Session::Ptr zwaveSession_ = nullptr;
	NodesManager::Ptr nodesServiceRegisterHandler_ = nullptr;
	ServiceRef::Ptr serviceRef_ = nullptr;
	std::function<void(Way::Event)> callback_ = [&] (Way::Event event)
	{
		Poco::Logger& log = bundleContext_->logger();
		log.debug("DeviceAddCallback called with %#x %#x %#x ", event.nodeId(), event.commandClass(), event.instanceId());
		switch(event.eventType()) {
		case Way::Event::DeviceAdded:
			nodesServiceRegisterHandler_->deviceAdded(event);
			break;
		case Way::Event::DeviceRemoved:
			nodesServiceRegisterHandler_->deviceRemoved(event);
			break;
		case Way::Event::CommandAdded:
			nodesServiceRegisterHandler_->commandAdded(event);
			break;
		case Way::Event::CommandRemoved:
			nodesServiceRegisterHandler_->commandRemoved(event);
			break;
		case Way::Event::InstanceAdded:
			nodesServiceRegisterHandler_->instanceAdded(event);
			break;
		case Way::Event::InstanceRemoved:
			nodesServiceRegisterHandler_->instanceRemoved(event);
			break;
		case Way::Event::Unknown:
			nodesServiceRegisterHandler_->unknown(event);
			break;
		}
	};
};


} } // namespace IoT::ZWave


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::ZWave::BundleActivator)
POCO_END_MANIFEST
