#include "IoT/ZWave/Service.h"

#include <string>


namespace IoT {
namespace ZWave {


Service::Service(Way::Controller::Ptr controller,
	NodesManager::Ptr nodesServiceHandler)
	: controller_(controller), nodesServiceHandler_(nodesServiceHandler)
{
}

const std::type_info& Service::type() const { return typeid(Service); }

bool Service::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name() || Service::isA(otherType);
}

Way::Error Service::resetControllerToFactoryDefault()
{
	nodesServiceHandler_->removeAllNodes();
	return controller_->resetToFactoryDefault();
	//TODO(jboe): register here z-wave controller "one" in OSGi
}

Way::Error Service::inclusionMode(bool on)
{
	return controller_->inclusionMode(on);
}

Way::Error Service::exclusionMode(bool on)
{
	return controller_->exclusionMode(on);
}


} } // namespace IoT::ZWave
