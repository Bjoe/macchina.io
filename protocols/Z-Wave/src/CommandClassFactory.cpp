#include "CommandClassFactory.h"

#include "IoT/ZWave/CommandClass/Basic.h"
#include "IoT/ZWave/CommandClass/Hail.h"
#include "IoT/ZWave/CommandClass/NoOperation.h"
#include "IoT/ZWave/CommandClass/SwitchBinary.h"
#include "IoT/ZWave/CommandClass/Meter.h"
#include "IoT/ZWave/CommandClass/Unknown.h"

namespace IoT {
namespace ZWave {

BaseCommandClass::Ptr CommandClassFactory::create(
		const Way::Controller::Ptr& controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId commandId)
{
	BaseCommandClass::Ptr commandClass;
	switch(commandId)
	{
		case IoT::ZWave::CommandClass::Basic::CLASS_ID:
			commandClass = new IoT::ZWave::CommandClass::Basic(controller, identifier, instance);
			break;
		case IoT::ZWave::CommandClass::Hail::CLASS_ID:
			commandClass = new IoT::ZWave::CommandClass::Hail(controller, identifier, instance);
			break;
		case IoT::ZWave::CommandClass::NoOperation::CLASS_ID:
			commandClass = new IoT::ZWave::CommandClass::NoOperation(controller, identifier, instance);
			break;
		case IoT::ZWave::CommandClass::SwitchBinary::CLASS_ID:
			commandClass = new IoT::ZWave::CommandClass::SwitchBinary(controller, identifier, instance);
			break;
		case IoT::ZWave::CommandClass::Meter::CLASS_ID:
			commandClass = new IoT::ZWave::CommandClass::Meter(controller, identifier, instance);
			break;
		default:
			commandClass = new IoT::ZWave::CommandClass::Unknown(controller, identifier, instance, commandId);
			break;
	}
	return commandClass;
}

} } // namespace IoT::ZWave
