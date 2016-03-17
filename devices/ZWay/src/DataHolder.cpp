#include "IoT/ZWave/Way/DataHolder.h"

#include "ZDefsPublic.h"
#include "ZData.h"

namespace IoT {
namespace ZWave {
namespace Way {


Poco::Dynamic::Var::Ptr DataHolder::getValue() const
{
	return getValueFromDataHolder();
}

IoT::ZWave::Way::DataHolderEvent::Ptr DataHolder::createDataChangeEvent()
{
	return createInstance();
}


} } } // namespace IoT::ZWave::Way
