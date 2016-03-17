#include "IoT/ZWave/Way/CommandClass/Basic.h"

#include "ZWayController.h"
#include "ZWayError.h"
#include "CommandClassesPublic.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace CommandClass {


Basic::Basic(Controller::Ptr controller) : controller_(controller)
{

}

Error Basic::get(NodeIdentifier identifier, NodeInstance instance)
{
	Error error = controller_->error();
	if (error.isNoError()) {
		ZWay zw = ZWayController::convert(controller_);
		ZWBYTE nodeId = identifier;
		ZWBYTE instanceId = instance;
		ZWError e = zway_cc_basic_get(
			zw,
			nodeId,
			instanceId,
			nullptr,
			nullptr,
			nullptr); // ZJobCustomCallback successCallback, ZJobCustomCallback
			   // failureCallback, void* callbackArg);
		if (e != NoError)
		{
			ZWayError zwerror = ZWayError("Report value failed", e);
			error = zwerror.error();
		}
	}
	return error;
}

Error Basic::set(NodeIdentifier identifier, NodeInstance instance, const Poco::Dynamic::Var& val)
{
	Error error = controller_->error();
	if (error.isNoError()) {
		ZWay zw = ZWayController::convert(controller_);
		ZWBYTE nodeId = identifier;
		ZWBYTE instanceId = instance;
		ZWBYTE value = val.convert<ZWBYTE>();
		ZWError e = zway_cc_basic_set(
			zw,
			nodeId,
			instanceId,
			value,
			nullptr,
			nullptr,
			nullptr); // ZJobCustomCallback successCallback, ZJobCustomCallback
			   // failureCallback, void* callbackArg);
		if (e != NoError)
		{
			ZWayError zwerror = ZWayError("Set value failed", e);
			error = zwerror.error();
		}
	}
	return error;
}


} } } }
