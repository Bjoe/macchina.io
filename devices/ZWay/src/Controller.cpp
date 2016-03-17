#include "IoT/ZWave/Way/Controller.h"

#include "ZWayController.h"
#include "Poco/StringTokenizer.h"
#include <string>
#include "ZDefsPublic.h"
#include "ZWayError.h"
#include "ZPlatform.h"
#include "ZWayLib.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace {

ZWayError isZWayReady(ZWay zWay)
{
	ZWayError error;
	if (zway_is_running(zWay) == 0u)
	{
		error = ZWayError("ZWay is not running");
	}

	/* TODO found a solution
	 *  while(!zway_is_idle(zWay))
  {
	sleep_ms(10);
  } */
	return error;
}


}

bool Controller::isInterviewiDone(NodeIdentifier identifier) const
{
	bool result = false;
	if (isZWayReady(ZWayController::convert(this)).error().isNoError())
	{
		ZWBYTE deviceId = identifier;
		zdata_acquire_lock(ZDataRoot(ZWayController::convert(this)));
		ZWBOOL b = zway_device_is_interview_done(ZWayController::convert(this), deviceId);
		zdata_release_lock(ZDataRoot(ZWayController::convert(this)));
		result = (b != 0u);
	}
	return result;
}

Error Controller::forceDeviceInterview(NodeIdentifier identifier) const
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBYTE deviceId = identifier;
		ZWError e = zway_device_interview_force(ZWayController::convert(this), deviceId);
		if (e != NoError)
		{
			error = ZWayError("Force device interview failed", e);
		}
	}
	return error.error();
}

Error Controller::runCommandClassInterview(
	NodeIdentifier identifier,
	NodeInstance instance,
	CommandClassId classId) const
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBYTE deviceId = identifier;
		ZWBYTE instanceId = instance;
		ZWBYTE ccId = classId;
		ZWError e = zway_command_interview(ZWayController::convert(this), deviceId, instanceId, ccId);
		if (e != NoError)
		{
			error = ZWayError("Run command class interview failed", e);
		}
	}
	return error.error();
}

Error Controller::sendDeviceNop(NodeIdentifier identifier) const
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBYTE nodeId = identifier;
		ZWError e = zway_device_send_nop(ZWayController::convert(this), nodeId, NULL, NULL, NULL);
		if (e != NoError)
		{
			error = ZWayError("Send device NOP failed", e);
		}
	}
	return error.error();
}

Error Controller::loadXmlForDevice(NodeIdentifier identifier, const std::string& fileName) const
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBYTE nodeId = identifier;
		ZWCSTR fName = fileName.c_str();
		ZWError e = zway_device_load_xml(ZWayController::convert(this), nodeId, fName);
		if (e != NoError)
		{
			error = ZWayError("Load XML/ZDDX files failed", e);
		}
	}
	return error.error();
}

void Controller::deviceAwakeQueue(NodeIdentifier identifier)
{
	if (isZWayReady(ZWayController::convert(this)).error().isError())
	{
		ZWBYTE nodeId = identifier;
		zway_device_awake_queue(ZWayController::convert(this), nodeId);
	}
}

Error Controller::resetToFactoryDefault()
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWError r = zway_fc_set_default(ZWayController::convert(this), nullptr, nullptr, nullptr);
		if (r != NoError)
		{
			error = ZWayError("Reset to factory default failed", r);
		}
	}
	return error.error();
}

Error Controller::inclusionMode(bool on)
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBOOL startStop = FALSE;
		if (on)
		{
			startStop = TRUE;
		}

		ZWError r = zway_fc_add_node_to_network(
			ZWayController::convert(this), startStop, TRUE, nullptr, nullptr, nullptr);
		if (r != NoError)
		{
			error = ZWayError("Inclusion mode error", r);
		}
	}
	return error.error();
}

Error Controller::exclusionMode(bool on)
{
	ZWayError error = isZWayReady(ZWayController::convert(this));
	if (error.error().isNoError())
	{
		ZWBOOL startStop = FALSE;
		if (on)
		{
			startStop = TRUE;
		}
		ZWError r = zway_fc_remove_node_from_network(
			ZWayController::convert(this), startStop, TRUE, nullptr, nullptr, nullptr);
		if (r != NoError)
		{
			error = ZWayError("Exclusion mode error", r);
		}
	}
	return error.error();;
}

Error Controller::error() const
{
	return isZWayReady(ZWayController::convert(this)).error();
}


} } } // namespace IoT::ZWave::Device
