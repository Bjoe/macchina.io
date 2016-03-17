#include "IoT/ZWave/Way/CommandClass/Meter.h"

#include "ZWayController.h"
#include "ZWayError.h"
#include "CommandClassesPublic.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace CommandClass {


Meter::Meter(Controller::Ptr controller) : controller_(controller)
{

}

Error Meter::get(NodeIdentifier identifier, NodeInstance instance, int scale)
{
	Error error = controller_->error();
	if (error.isNoError())
	{
		ZWay zw = ZWayController::convert(controller_);
		ZWBYTE nodeId = identifier;
		ZWBYTE instanceId = instance;
		ZWError e = zway_cc_meter_get(
			zw,
			nodeId,
			instanceId,
			scale,
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


} } } }
