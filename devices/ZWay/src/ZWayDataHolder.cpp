#include "ZWayDataHolder.h"

#include "ZWayController.h"
#include "ZWayDataHolderEvent.h"
#include "DataUtil.h"


namespace IoT {
namespace ZWave {
namespace Way {


ZWayDataHolder::ZWayDataHolder(Controller::Ptr controller)
	: controller_(controller)
{

}

void ZWayDataHolder::setData(ZDataHolder data)
{
	data_ = data;
}

Poco::Dynamic::Var::Ptr ZWayDataHolder::getValueFromDataHolder() const
{
	ZWay zway = ZWayController::convert(controller_);
	zdata_acquire_lock(ZDataRoot(zway));
	Poco::Dynamic::Var::Ptr value = DataUtil::getDataValue(data_);
	zdata_release_lock(ZDataRoot(zway));
	return value;
}

DataHolderEvent::Ptr ZWayDataHolder::createInstance()
{
	Poco::SharedPtr<ZWayDataHolderEvent> holderEvent = new ZWayDataHolderEvent(controller_);
	holderEvent->setData(data_);
	return holderEvent;
}


} } } // namespace IoT::ZWave::Way
