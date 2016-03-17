#include "IoT/ZWave/CommandClass/Meter.h"

#include "IoT/ZWave/Way/DataHolderFactory.h"
#include "IoT/ZWave/Way/CommandClass/Meter.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId Meter::CLASS_ID;

Meter::Meter(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
	: BaseCommandClass(controller, identifier, instance, Meter::CLASS_ID)
{
}

Scales Meter::getScales() const
{
	std::map<std::string, Way::DataHolder::Ptr> dataHolders =
		Way::DataHolderFactory::createCommandClassHolders(
			controller_, identifier_, instance_, Meter::CLASS_ID);
	return Scales::createInstance(
		controller_, identifier_, instance_, classId_, dataHolders);
}

Way::CommandClassId Meter::commandClassId() const { return CLASS_ID; }

std::string Meter::commandClassName() const { return "COMMAND_CLASS_METER"; }

Way::Error Meter::reportValue() const
{
	int scale = -1; // get all scales
	Way::CommandClass::Meter meter(controller_);
	return meter.get(identifier_, instance_, scale);
}

Poco::Dynamic::Var::Ptr Meter::getValue() const
{
	return getDataHolderValue("not_available");
}

Way::DataHolder::Ptr Meter::getDataHolder() const
{
	return BaseCommandClass::getDataHolder("not_available");
}

Way::Error Meter::setValue(const Poco::Dynamic::Var& /*val*/)
{
	return Way::Error("Set is not supported on ZWave Meter command", 1);
}


} } } // namespace IoT::ZWave::CommandClass
