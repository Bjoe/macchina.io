#include "IoT/ZWave/Way/Session.h"

#include <cstdio>

#include "Poco/OSP/Configuration.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/ServiceFinder.h"

#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Event.h"
#include "ZWayController.h"
#include "ZWayError.h"
#include "ZErrors.h"
#include "ZWayLib.h"


namespace IoT {
namespace ZWave {
namespace Way {


void zwayDeviceAddCb(
	ZWay /*unused*/,
	ZWDeviceChangeType type,
	ZWBYTE node_id,
	ZWBYTE instance_id,
	ZWBYTE command_id,
	void* arg)
{
	Event::Type eventType = static_cast<Event::Type>(type);
	Event event(eventType, node_id, instance_id, command_id);
    std::function<void(Event)>* callback = static_cast<std::function<void(Event)>*>(arg);
    (*callback)(event);
}

void zwayTerminatedCb(ZWay /*zWay*/, void* arg)
{
    std::function<void()>* callback = static_cast<std::function<void()>*>(arg);
    (*callback)();
}

Session::~Session()
{
	ZWay z = ZWayController::convert(controller_);
	zway_terminate(&z);
}

Controller::Ptr Session::controller() const
{
	return controller_;
}

Session::Ptr Session::createInstance(
	const Poco::OSP::BundleContext::Ptr& bundleContext,
	const std::string& instanceName,
	Poco::Logger& log)
{
	Poco::OSP::PreferencesService::Ptr preferencesService =
		Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(
			bundleContext);
	Poco::OSP::Configuration::Ptr configuration = preferencesService->configuration();

	std::string device = configuration->getString("z-wave.device");
	std::string configFolder = configuration->getString("z-wave.config_folder");
	std::string translationFolder =	configuration->getString("z-wave.translation_folder");
	std::string zddxFolder = configuration->getString("z-wave.zddx_folder");
	std::string zwayLog = configuration->getString("z-wave.logfile");
	int zwayLogLevel = configuration->getInt("z-wave.loglevel");

	const char* zwLog = zwayLog.c_str();
	std::FILE* fp = std::fopen(zwLog, "w");
	ZWLog zWLog = zlog_create(fp, zwayLogLevel);

	const char* port = device.c_str();
	const char* configFld = configFolder.c_str();
	const char* translationFld = translationFolder.c_str();
	const char* zddxFld = zddxFolder.c_str();
	const char* instanceNm = instanceName.c_str();
	ZWay zWay = nullptr;
	ZWError zWError = zway_init(&zWay, port, configFld, translationFld, zddxFld, instanceNm, zWLog);
	ZWayError zwayError = ZWayError();
	if (zWError != NoError)
	{
		zwayError = ZWayError("Failed to init ZWay", zWError);
	}
	Error error = zwayError.error();
	Controller::Ptr controller = new ZWayController(zWay);
	return new Session(controller, log, error);
}

Way::Error Session::start(std::function<void(Event)> deviceAddCallback)
{
	if(error_.isNoError())
	{
		ZWay zw = ZWayController::convert(controller_);
		ZWError zWError = zway_device_add_callback(
			zw,
			DeviceAdded | DeviceRemoved | InstanceAdded | InstanceRemoved | CommandAdded | CommandRemoved,
			zwayDeviceAddCb,
			&deviceAddCallback);
		if (zWError != NoError)
		{
			ZWayError zwayError = ZWayError("ZWay add callback faild with error", zWError);
			return zwayError.error();
		}
		zWError = zway_start(zw, zwayTerminatedCb, &terminatedCallback_);
		if (zWError != NoError)
		{
			ZWayError zwayError = ZWayError("Failed to start ZWay", zWError);
			return zwayError.error();
		}

		zWError = zway_discover(zw);
		if (zWError != NoError)
		{
			ZWayError zwayError = ZWayError("Failed to negotiate with Z-Wave stick", zWError);
			return zwayError.error();
		}

		ZWayError zwayError = ZWayError();
		error_ = zwayError.error();
	}
	return error_;
}

Way::Error Session::stop()
{
	if(error_.isNoError())
	{
		ZWay zw = ZWayController::convert(controller_);
		ZWError zWError = zway_stop(zw);
		if (zWError != NoError)
		{
			ZWayError zwayError = ZWayError("ZWay faild to stop", zWError);
			return zwayError.error();
		}
		ZWayError zwayError = ZWayError();
		error_ = zwayError.error();
	}
	return error_;
}

Error Session::error()
{
	return error_;
}

Session::Session(
	Controller::Ptr controller,
	Poco::Logger& log,
	Error error)
	: controller_(controller),
	  log_(log),
	  error_(error)
{
}


} } } // namespace IoT::ZWave::Way
