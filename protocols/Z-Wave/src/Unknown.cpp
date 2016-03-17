#include "IoT/ZWave/CommandClass/Unknown.h"

#include "Poco/Format.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId Unknown::CLASS_ID;

Unknown::Unknown(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId)
	: BaseCommandClass(controller, identifier, instance, classId), classId_(classId)
{
}

Way::CommandClassId Unknown::commandClassId() const { return classId_; }

std::string Unknown::commandClassName() const
{
	return Poco::format("COMMAND_CLASS_UNKNOWN_%#x", classId_);
}


} } } // namespace IoT::ZWave::CommandClass
