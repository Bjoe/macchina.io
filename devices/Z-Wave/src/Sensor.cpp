#include "Sensor.h"

#include "Poco/Delegate.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/NumberFormatter.h"

#include "IoT/ZWave/Way/DataHolder.h"


namespace IoT {
namespace ZWave {
namespace Devices {


Sensor::Sensor(Poco::Any deviceIdentifire, Poco::Logger& log, Scale::Ptr scale)
	: deviceIdentifier_(deviceIdentifire),
	  log_(log),
	  scale_(scale)
{
	addProperty("deviceIdentifier", &Sensor::getDeviceIdentifier);
	addProperty("symbolicName", &Sensor::getSymbolicName);
	addProperty("name", &Sensor::getName);
	addProperty("displayName", &Sensor::getDisplayValue);
	addProperty("physicalQuantity", &Sensor::getPhysicalQuantity);
	addProperty("physicalUnit", &Sensor::getPhysicalUnit);
	addProperty("displayValue", &Sensor::getDisplayValue);

	Way::DataHolder::Ptr holder = scale_->getDataHolder();
	dataEvent_ = holder->createDataChangeEvent();
	dataEvent_->event_ += Poco::delegate(this, &IoT::ZWave::Devices::Sensor::update);
	dataEvent_->registerDataChangeEvent();
}

Sensor::~Sensor()
{
	dataEvent_->event_ -= Poco::delegate(this, &IoT::ZWave::Devices::Sensor::update);
	dataEvent_->unregisterDataChangeEvent();
}

double Sensor::value() const
{
	// scale_->reportValue(); ???
	return scale_->getValue();
}

bool Sensor::ready() const { return true; }

void Sensor::update(const void* /*pSender*/, Poco::Dynamic::Var::Ptr& value)
{
	double result = value->convert<double>();
	std::string msg("Value changed for ");
	msg.append(scale_->getSensorName());
	msg.append(" ");
	msg.append(Poco::NumberFormatter::format(result, 0, 1));
	msg.append(" ");
	msg.append(scale_->getName());
	log_.information(msg);
	eventPolicy_->valueChanged(result);
}

Poco::Any Sensor::getName(const std::string& /*unused*/) const { return std::string(NAME); }

Poco::Any Sensor::getSymbolicName(const std::string& /*unused*/) const
{
	return std::string(SYMBOLIC_NAME);
}

Poco::Any Sensor::getDeviceIdentifier(const std::string& /*unused*/) const
{
	return deviceIdentifier_;
}

Poco::Any Sensor::getDisplayValue(const std::string& /*unused*/) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}

Poco::Any Sensor::getPhysicalQuantity(const std::string& /*unused*/) const
{
	return scale_->getSensorName();
}

Poco::Any Sensor::getPhysicalUnit(const std::string& /*unused*/) const
{
	return scale_->getName();
}


} } } // namespace IoT::ZWave::Devices
