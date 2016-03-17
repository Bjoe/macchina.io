#include "IoT/ZWave/CommandClass/SwitchBinary.h"

#include "Poco/Tuple.h"
#include "IoT/ZWave/Way/CommandClass/SwitchBinary.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId SwitchBinary::CLASS_ID;

SwitchBinary::SwitchBinary(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
	: BaseCommandClass(controller, identifier, instance, SwitchBinary::CLASS_ID)
{
}

Way::Error SwitchBinary::setOn()
{
	unsigned char val = 1;
	Poco::Dynamic::Var value(val);
	return setValue(value);
}

Way::Error SwitchBinary::setOff()
{
	unsigned char val = 0;
	Poco::Dynamic::Var value(val);
	return setValue(value);
}

bool SwitchBinary::isOn() const
{
	bool result = false;
	Poco::Dynamic::Var::Ptr value = getValue();
	if (!value->isEmpty())
	{
		result = value->extract<bool>();
	}
	return result;
}

bool SwitchBinary::isOff() const { return (!isOn()); }

Way::CommandClassId SwitchBinary::commandClassId() const { return CLASS_ID; }

std::string SwitchBinary::commandClassName() const
{
	return "COMMAND_CLASS_SWITCHBINARY";
}

Way::Error SwitchBinary::reportValue() const
{
	Way::CommandClass::SwitchBinary switchBinary(controller_);
	return switchBinary.get(identifier_, instance_);
}

Poco::Dynamic::Var::Ptr SwitchBinary::getValue() const
{
	return getDataHolderValue("level");
}

Way::DataHolder::Ptr SwitchBinary::getDataHolder() const
{
	return BaseCommandClass::getDataHolder("level");
}

Way::Error SwitchBinary::setValue(const Poco::Dynamic::Var& val)
{
	Way::CommandClass::SwitchBinary switchBinary(controller_);
	return switchBinary.set(identifier_, instance_, val);
}


} } } // namespace IoT::ZWave::CommandClass
