#include "ResetController.h"

#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"

#include "IoT/ZWave/Way/Error.h"
#include "IoT/ZWave/Service.h"


namespace IoT {
namespace Web {
namespace ZWave {
namespace Command {


ResetController::ResetController() {}

Poco::JSON::Object ResetController::handle(
	Poco::OSP::BundleContext::Ptr bundleContext,
	Poco::SharedPtr<Poco::Net::HTMLForm> /*form*/) const
{
	Poco::JSON::Object result;
	Poco::OSP::ServiceRef::Ptr serviceRef =	bundleContext->registry().findByName(IoT::ZWave::Service::SERVICE_NAME);
	if (!serviceRef.isNull())
	{
		IoT::ZWave::Service::Ptr zwayService = serviceRef->castedInstance<IoT::ZWave::Service>();
		IoT::ZWave::Way::Error zWayError = zwayService->resetControllerToFactoryDefault();
		if (zWayError.isNoError())
		{
			result.set("state", "ok");
		}
		else
		{
			result.set("state", zWayError.errorMessage());
		}
	}
	else
	{
		result.set("state", "no zway service availabe");
	}
	return result;
}


} } } } // namespace IoT::Web::ZWave::Command
