#include "ZWayController.h"

namespace IoT {
namespace ZWave {
namespace Way {

ZWay ZWayController::convert(const Controller* controller)
{
	const ZWayController* zwayController = reinterpret_cast<const ZWayController*>(controller);
	return zwayController->instance();
}

ZWayController::ZWayController(ZWay zway) : zWay_(zway)
{
}

ZWay ZWayController::instance() const
{
	return zWay_;
}

} // namespace Way
} // namespace ZWave
} // namespace IoT
