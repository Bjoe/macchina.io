#include "Basic.h"

#include "Poco/Delegate.h"
#include "Poco/NumberFormatter.h"


namespace IoT {
namespace ZWave {
namespace Devices {


Basic::Basic(
        Poco::Any deviceIdentifier,
        Poco::Logger &logger,
        CommandClass::Basic::Ptr basic)
    : deviceIdentifier_(deviceIdentifier),
      logger_(logger),
      basic_(basic)
{
    addProperty("deviceIdentifier", &Basic::getDeviceIdentifier);
    addProperty("symbolicName", &Basic::getSymbolicName);
    addProperty("name", &Basic::getName);
    addProperty("displayValue", &Basic::getDisplayValue);

    Way::DataHolder::Ptr holder = basic_->getDataHolder();
    dataEvent_ = holder->createDataChangeEvent();
    dataEvent_->event_ += Poco::delegate(this, &IoT::ZWave::Devices::Basic::update);
    dataEvent_->registerDataChangeEvent();
}

Basic::~Basic()
{
    dataEvent_->event_ -= Poco::delegate(this, &IoT::ZWave::Devices::Basic::update);
    dataEvent_->unregisterDataChangeEvent();
}

void Basic::set(int value)
{
    if(value > 255)
    {
        value = 255;
    }
    if(value < 0)
    {
        value = 0;
    }
    logging(basic_->setValue(value));
}

int Basic::get() const
{
    int result = 0;
    Poco::Dynamic::Var::Ptr value = basic_->getValue();
    if(!value->isEmpty())
    {
        result = value->convert<int>();
    }
    return result;
}

Poco::Any Basic::getName(const std::string& /*unused*/) const
{
    return std::string(NAME);
}

Poco::Any Basic::getSymbolicName(const std::string& /*unused*/) const
{
    return std::string(SYMBOLIC_NAME);
}

Poco::Any Basic::getDeviceIdentifier(const std::string& /*unused*/) const
{
    return deviceIdentifier_;
}

Poco::Any Basic::getDisplayValue(const std::string& /*unused*/) const
{
    return Poco::NumberFormatter::format(get(), 3);
}

void Basic::update(const void* /*unused*/, Poco::Dynamic::Var::Ptr &value)
{
    int intVal = 0;
    if(!value->isEmpty())
    {
        intVal = value->convert<int>();
    }
    eventPolicy_->valueChanged(intVal);
}

void Basic::logging(const Way::Error &error)
{
    if (error.isError())
    {
        std::string msg = error.errorMessage();
        logger_.error(msg);
    }
}

} // namespace Devices
} // namespace ZWave
} // namespace IoT
