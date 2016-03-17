#include "ServiceState.h"

#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"

#include "IoT/ZWave/Service.h"


namespace IoT {
namespace Web {
namespace ZWave {
namespace Command {


ServiceState::ServiceState() {}

Poco::JSON::Object ServiceState::handle(
	Poco::OSP::BundleContext::Ptr bundleContext,
	Poco::SharedPtr<Poco::Net::HTMLForm> /*form*/) const
{
	Poco::JSON::Object result;
	Poco::OSP::ServiceRef::Ptr serviceRef = bundleContext->registry().findByName(IoT::ZWave::Service::SERVICE_NAME);
	if (!serviceRef.isNull())
	{
		result.set("zwaveServiceState", "online");
	}
	else
	{
		result.set("zwaveServiceState", "offline");
	}
	return result;
}


} } } } // namespace IoT::Web::ZWave::Command
