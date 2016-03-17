#include "IoT/ZWave/Way/CommandClass/SwitchBinary.h"

#include "ZWayController.h"
#include "ZWayError.h"
#include "CommandClassesPublic.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace CommandClass {


SwitchBinary::SwitchBinary(Controller::Ptr controller) : controller_(controller)
{

}

Error SwitchBinary::get(NodeIdentifier identifier, NodeInstance instance)
{
	Error error = controller_->error();
	if (error.isNoError())
	{
		ZWay zw = ZWayController::convert(controller_);
		ZWBYTE nodeId = identifier;
		ZWBYTE instanceId = instance;
		ZWError e = zway_cc_switch_binary_get(
			zw,
			nodeId,
			instanceId,
			nullptr,
			nullptr,
			nullptr);
		if (e != NoError)
		{
			ZWayError zwerror = ZWayError("Report value failed", e);
			error = zwerror.error();
		}
	}
	return error;
}

Error SwitchBinary::set(NodeIdentifier identifier, NodeInstance instance, const Poco::Dynamic::Var& val)
{
	Error error = controller_->error();
	if (error.isNoError())
	{
		ZWay zw = ZWayController::convert(controller_);
		ZWBYTE nodeId = identifier;
		ZWBYTE instanceId = instance;
		ZWBYTE value = val.convert<ZWBYTE>();
		ZWError e = zway_cc_switch_binary_set(
			zw,
			nodeId,
			instanceId,
			value,
			nullptr,
			nullptr,
			nullptr);
		if (e != NoError)
		{
			ZWayError zwerror = ZWayError("Set value failed", e);
			error = zwerror.error();
		}
	}
	return error;
}


} } } }
