#include "IoT/ZWave/Way/DataHolderEvent.h"

#include "DataUtil.h"
#include "ZWayController.h"
#include "Poco/Dynamic/Var.h"


namespace IoT {
namespace ZWave {
namespace Way {


DataHolderEvent::DataHolderEvent(Way::Controller::Ptr controller)
	: event_(), controller_(controller)
{
}

Error DataHolderEvent::registerDataChangeEvent()
{
	ZWay zway = ZWayController::convert(controller_);
	zdata_acquire_lock(ZDataRoot(zway));
	Way::Error error = registerEvent();
	zdata_release_lock(ZDataRoot(zway));
	return error;
}

Way::Error DataHolderEvent::unregisterDataChangeEvent()
{
	ZWay zway = ZWayController::convert(controller_);
	zdata_acquire_lock(ZDataRoot(zway));
	Way::Error error = unregisterEvent();
	zdata_release_lock(ZDataRoot(zway));
	return error;
}

void DataHolderEvent::notify(Poco::Dynamic::Var::Ptr value)
{
	event_.notify(this, value);
}


} } } // namespace IoT::ZWave::Way
