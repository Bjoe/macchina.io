#include "ServiceHandler.h"

#include "Basic.h"
#include "Sensor.h"
#include "SwitchBinary.h"

#include "Poco/Logger.h"
#include "Poco/NumericString.h"
#include "Poco/OSP/Properties.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/String.h"

#include "IoT/Devices/Basic.h"
#include "IoT/Devices/BasicServerHelper.h"
#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/SwitchBinary.h"
#include "IoT/Devices/SwitchBinaryServerHelper.h"

#include "IoT/ZWave/CommandClass/Basic.h"
#include "IoT/ZWave/CommandClass/Meter.h"
#include "IoT/ZWave/CommandClass/SwitchBinary.h"
#include "IoT/ZWave/Node.h"
#include "IoT/ZWave/Scale.h"
#include "IoT/ZWave/Scales.h"
#include "IoT/ZWave/Way/Defs.h"

#include <map>


namespace IoT {
namespace ZWave {
namespace Devices {


ServiceHandler::ServiceHandler(Poco::OSP::BundleContext::Ptr context)
	: context_(context)
{
}

void ServiceHandler::registerService(Poco::OSP::ServiceRef::ConstPtr& serviceRef)
{
	IoT::ZWave::Node::Ptr node = serviceRef->castedInstance<IoT::ZWave::Node>();
	Poco::Logger& log = context_->logger();

	IoT::ZWave::Way::NodeIdentifier id = node->id();
	std::string idStr;
	Poco::uIntToStr(id, 10, idStr);

    IoT::ZWave::CommandClass::Basic::Ptr basic = node->findCommandClass<IoT::ZWave::CommandClass::Basic>();
    if(!basic.isNull())
    {
        std::string oid(IoT::ZWave::Devices::Basic::SYMBOLIC_NAME);
        oid += "#";
        oid += idStr;

        Poco::SharedPtr<IoT::ZWave::Devices::Basic> instance = new IoT::ZWave::Devices::Basic(oid, log, basic);

        using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Devices::Basic>;
        ServerHelper::RemoteObjectPtr remoteObject = ServerHelper::createRemoteObject(instance, oid);

        Poco::OSP::Properties props;
        props.set("io.macchina.device", IoT::ZWave::Devices::Basic::SYMBOLIC_NAME);
        props.set("io.macchina.physicalQuantity", "0-255");

        std::string logMsg("Found zwave basic id: ");
        logMsg.append(idStr);
        log.information(logMsg);

        Poco::OSP::ServiceRef::Ptr serviceRef = context_->registry().registerService(oid, remoteObject, props);

        const std::string serviceName = serviceRef->name();
        serviceRefs_[serviceName] = serviceRef;
    }

	IoT::ZWave::CommandClass::SwitchBinary::Ptr switchBinary = node->findCommandClass<IoT::ZWave::CommandClass::SwitchBinary>();
	if (!switchBinary.isNull())
	{
		std::string oid(IoT::ZWave::Devices::SwitchBinary::SYMBOLIC_NAME);
		oid += "#";
		oid += idStr;

		Poco::SharedPtr<IoT::ZWave::Devices::SwitchBinary> instance = new IoT::ZWave::Devices::SwitchBinary(oid, log, switchBinary);

		using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Devices::SwitchBinary>;
		ServerHelper::RemoteObjectPtr remoteObject = ServerHelper::createRemoteObject(instance, oid);

		Poco::OSP::Properties props;
		props.set("io.macchina.device",	IoT::ZWave::Devices::SwitchBinary::SYMBOLIC_NAME);
		props.set("io.macchina.physicalQuantity", "On/Off");

		std::string logMsg("Found zwave switch binary id: ");
		logMsg.append(idStr);
		log.information(logMsg);

		Poco::OSP::ServiceRef::Ptr serviceRef =	context_->registry().registerService(oid, remoteObject, props);

		const std::string serviceName = serviceRef->name();
		serviceRefs_[serviceName] = serviceRef;
	}

	IoT::ZWave::CommandClass::Meter::Ptr meter = node->findCommandClass<IoT::ZWave::CommandClass::Meter>();
	if (!meter.isNull())
	{
		IoT::ZWave::Scales scales = meter->getScales();

		std::map<IoT::ZWave::Scale::Type, IoT::ZWave::Scale::Ptr> scalesMap = scales.getScales();
		for (auto& iter : scalesMap)
		{
			IoT::ZWave::Scale::Ptr scale = iter.second;
			std::string physicalQuantityWithSpace = scale->getSensorName();
			std::string physicalUnitWithSpace = scale->getName();

			std::string physicalQuantity = Poco::replace(physicalQuantityWithSpace, " ", "_");
			std::string physicalUnit = Poco::replace(physicalUnitWithSpace, " ", "_");

			std::string oid(IoT::ZWave::Devices::Sensor::SYMBOLIC_NAME);
			oid += "#";
			oid += physicalQuantity;
			oid += ".";
			oid += physicalUnit;
			oid += ".";
			oid += idStr;

			Poco::SharedPtr<IoT::ZWave::Devices::Sensor> instance = new IoT::ZWave::Devices::Sensor(oid, log, scale);

			using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor>;
			ServerHelper::RemoteObjectPtr remoteObject = ServerHelper::createRemoteObject(instance, oid);

			Poco::OSP::Properties props;
			props.set("io.macchina.device", IoT::ZWave::Devices::Sensor::SYMBOLIC_NAME);
			props.set("io.macchina.physicalQuantity", physicalQuantity);
			props.set("io.macchina.physicalUnit", physicalUnit);

			std::string logMsg("Found zwave meter id:");
			logMsg.append(idStr);
			logMsg.append(" with sensor ");
			logMsg.append(physicalQuantity);
			logMsg.append(" and scale ");
			logMsg.append(physicalUnit);
			log.information(logMsg);

			Poco::OSP::ServiceRef::Ptr serviceRef =	context_->registry().registerService(oid, remoteObject, props);

			const std::string serviceName = serviceRef->name();
			serviceRefs_[serviceName] = serviceRef;
		}
		meter->reportValue();
	}
}

void ServiceHandler::unregisterService(Poco::OSP::ServiceRef::ConstPtr& serviceRef)
{
	const std::string serviceName = serviceRef->name();
	auto iter = serviceRefs_.find(serviceName);
	if (iter != serviceRefs_.end())
	{
		Poco::OSP::ServiceRef::Ptr localServiceRef = iter->second;
		context_->registry().unregisterService(localServiceRef);
		serviceRefs_.erase(iter);
	}
}


} } } // namespace IoT::ZWave::Devices
