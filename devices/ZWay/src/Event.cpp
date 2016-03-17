#include "IoT/ZWave/Way/Event.h"


namespace IoT {
namespace ZWave {
namespace Way {


Event::Event(
	Type eventType,
	NodeIdentifier nodeId,
	NodeInstance instanceId,
	CommandClassId commandClass)
	: eventType_(eventType),
	  nodeId_(nodeId),
	  instanceId_(instanceId),
	  commandClass_(commandClass)
{}

Event::Type Event::eventType() const { return eventType_; }

NodeIdentifier Event::nodeId() const { return nodeId_; }

NodeInstance Event::instanceId() const { return instanceId_; }

CommandClassId Event::commandClass() const { return commandClass_; }


} } } // namespace IoT::ZWave::Way
