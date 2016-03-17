#include "SwitchBinary.h"

#include "Poco/Delegate.h"
#include "Poco/Dynamic/Var.h"

#include "IoT/ZWave/Way/DataHolder.h"


namespace IoT {
namespace ZWave {
namespace Devices {


SwitchBinary::SwitchBinary(Poco::Any deviceIdentifier,
	Poco::Logger& log,
	CommandClass::SwitchBinary::Ptr switchBinary)
	: deviceIdentifier_(deviceIdentifier),
	  log_(log),
	  switchBinary_(switchBinary)
{
	addProperty("deviceIdentifier", &SwitchBinary::getDeviceIdentifier);
	addProperty("symbolicName", &SwitchBinary::getSymbolicName);
	addProperty("name", &SwitchBinary::getName);
	addProperty("displayValue", &SwitchBinary::getDisplayValue);

	Way::DataHolder::Ptr holder = switchBinary_->getDataHolder();
	dataEvent_ = holder->createDataChangeEvent();
	dataEvent_->event_ += Poco::delegate(this, &IoT::ZWave::Devices::SwitchBinary::update);
	dataEvent_->registerDataChangeEvent();
}

SwitchBinary::~SwitchBinary()
{
	dataEvent_->event_ -= Poco::delegate(this, &IoT::ZWave::Devices::SwitchBinary::update);
	dataEvent_->unregisterDataChangeEvent();
}

void SwitchBinary::setOn() { logging(switchBinary_->setOn()); }

void SwitchBinary::setOff() { logging(switchBinary_->setOff()); }

bool SwitchBinary::get() const { return switchBinary_->isOn(); }

void SwitchBinary::update(const void* /*unused*/, Poco::Dynamic::Var::Ptr& state)
{
	bool value = state->convert<bool>();
	if (value)
	{
		log_.information("Value changed: ON");
	}
	else
	{
		log_.information("Value changed: OFF");
	}
	eventPolicy_->valueChanged(value);
}

Poco::Any SwitchBinary::getName(const std::string& /*unused*/) const { return std::string(NAME); }

Poco::Any SwitchBinary::getSymbolicName(const std::string& /*unused*/) const
{
	return std::string(SYMBOLIC_NAME);
}

Poco::Any SwitchBinary::getDeviceIdentifier(const std::string& /*unused*/) const
{
	return deviceIdentifier_;
}

Poco::Any SwitchBinary::getDisplayValue(const std::string& /*unused*/) const
{
	std::string result("Off");
	if (get())
	{
		result = "On";
	}
	return result;
}

void SwitchBinary::logging(const Way::Error& error)
{
	if (error.isError())
	{
		std::string msg = error.errorMessage();
		log_.error(msg);
	}
}


} } } // namespace IoT::ZWave::Devices
