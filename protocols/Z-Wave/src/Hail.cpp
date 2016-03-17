#include "IoT/ZWave/CommandClass/Hail.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


const Way::CommandClassId Hail::CLASS_ID;

Hail::Hail(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
	: BaseCommandClass(controller, identifier, instance, Hail::CLASS_ID)
{
}

Way::CommandClassId Hail::commandClassId() const { return CLASS_ID; }

std::string Hail::commandClassName() const { return "COMMAND_CLASS_HAIL"; }


} } } // namespace IoT::ZWave::CommandClass
