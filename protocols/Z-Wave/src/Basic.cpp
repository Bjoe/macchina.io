#include "IoT/ZWave/CommandClass/Basic.h"

#include "Poco/Tuple.h"
#include "IoT/ZWave/Way/CommandClass/Basic.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId Basic::CLASS_ID;

Basic::Basic(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
	: BaseCommandClass(controller, identifier, instance, Basic::CLASS_ID)
{
}

Way::CommandClassId Basic::commandClassId() const { return CLASS_ID; }

std::string Basic::commandClassName() const { return "COMMAND_CLASS_BASIC"; }

Way::Error Basic::reportValue() const
{
	Way::CommandClass::Basic basic(controller_);
	return basic.get(identifier_, instance_);
}

Poco::Dynamic::Var::Ptr Basic::getValue() const
{
    return getDataHolderValue("level");
}

Way::DataHolder::Ptr Basic::getDataHolder() const
{
    return BaseCommandClass::getDataHolder("level");
}

Way::Error Basic::setValue(const Poco::Dynamic::Var& val)
{
	Way::CommandClass::Basic basic(controller_);
	return basic.set(identifier_, instance_, val);
}


} } } // namespace IoT::ZWave::CommandClass
