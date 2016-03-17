#include "IoT/ZWave/CommandClass/NoOperation.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId NoOperation::CLASS_ID;

NoOperation::NoOperation(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
	: BaseCommandClass(controller, identifier, instance, NoOperation::CLASS_ID)
{
}

Way::CommandClassId NoOperation::commandClassId() const { return CLASS_ID; }

std::string NoOperation::commandClassName() const
{
	return "COMMAND_CLASS_NO_OPERATION";
}


} } } // namespace IoT::ZWave::CommandClass
