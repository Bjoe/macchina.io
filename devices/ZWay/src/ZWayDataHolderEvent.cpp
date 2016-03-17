#include "ZWayDataHolderEvent.h"

#include "ZWayError.h"
#include "DataUtil.h"
#include "Poco/Dynamic/Var.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace {

void dataChangeCallback(
	ZDataRootObject /*root*/,
	ZWDataChangeType /*type*/,
	ZDataHolder data,
	void* arg)
{
	Poco::Dynamic::Var::Ptr value = DataUtil::getDataValue(data);
	if (!value->isEmpty())
	{
		ZWayDataHolderEvent* dataEvent = reinterpret_cast<ZWayDataHolderEvent*>(arg);
		dataEvent->notify(value);
	}
}


}


void ZWayDataHolderEvent::setData(ZDataHolder data)
{
	data_ = data;
}

Error ZWayDataHolderEvent::registerEvent()
{
	ZWayError error;
	// Attach callback function for Data holder change event
	// Supress add of duplicate address of function callback
	// ZWError e = zdata_add_callback(data_, dataChangeCallback, true,
	// dataEvent_);

	// Attach callback function for Data holder change event
	// Allows many callbacks with same address of callback function (but supress
	// duplicate callback/arg pair)
	ZWError e =	zdata_add_callback_ex(
				data_,
				dataChangeCallback,
				TRUE,
				this);

	if (e != NoError)
	{
		error = ZWayError("Register data change event failed.", e);
	}
	return error.error();
}

Error ZWayDataHolderEvent::unregisterEvent()
{
	ZWayError error;
	// ZWError e = zdata_remove_callback(data_ , dataChangeCallback);
	ZWError e = zdata_remove_callback_ex(data_, dataChangeCallback, this);
	if (e != NoError)
	{
		error = ZWayError("Unregister data change event failed.", e);
	}
	return error.error();
}


} } } // namespace IoT::ZWave::Way
