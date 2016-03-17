#include "IoT/ZWave/Scale.h"

#include "IoT/ZWave/Way/CommandClass/Meter.h"
#include "Poco/Dynamic/Var.h"

#include <utility>

namespace IoT {
namespace ZWave {


Scale::Scale(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	std::string dataPath,
	std::map<std::string, Way::DataHolder::Ptr> sensorDataHolders)
	: zWay_(controller),
	  identifier_(identifier),
	  instance_(instance),
	  dataPath_(std::move(dataPath)),
	  sensorDataHolders_(std::move(sensorDataHolders))
{
}

Scale::SensorType Scale::getSensorType() const
{
	Scale::SensorType result = Scale::UNKNOWN_SENSORTYPE;
	Way::DataHolder::Ptr dataHolder = getDataHolder("sensorType");
	Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
	if (!value->isEmpty())
	{
		int type = value->convert<int>();
		type *= 10;
		result = static_cast<Scale::SensorType>(type);
	}
	return result;
}

std::string Scale::getSensorName() const
{
	std::string result;
	Way::DataHolder::Ptr dataHolder = getDataHolder("sensorTypeString");
	Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
	if (!value->isEmpty())
	{
		result = value->convert<std::string>();
	}
	return result;
}

Scale::Type Scale::getType() const
{
	Scale::Type result = Scale::UNKNOWN_SCALE;
	Way::DataHolder::Ptr dataHolder = getDataHolder("scale");
	Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
	if (!value->isEmpty())
	{
		int val = value->convert<int>();
		result = static_cast<Scale::Type>(val);
	}
	return result;
}

std::string Scale::getName() const
{
	std::string result;
	Way::DataHolder::Ptr dataHolder = getDataHolder("scaleString");
	Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
	if (!value->isEmpty())
	{
		result = value->convert<std::string>();
	}
	return result;
}

Way::Error Scale::reportValue() const
{
	int scale = getType();
	Way::CommandClass::Meter meter(zWay_);
	return meter.get(identifier_, instance_, scale);
}


double Scale::getValue() const
{
	double result = -1;
	Way::DataHolder::Ptr dataHolder = getDataHolder("val");
	Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
	if (!value->isEmpty())
	{
		result = value->convert<double>();
	}
	return result;
}

Way::DataHolder::Ptr Scale::getDataHolder() const { return getDataHolder("val"); }

Way::DataHolder::Ptr Scale::getDataHolder(const std::string& name) const
{
	Way::DataHolder::Ptr dataHolder;
	auto iter =	sensorDataHolders_.find(dataPath_ + "." + name);
	if (iter != sensorDataHolders_.cend())
	{
		dataHolder = iter->second;
	}
	return dataHolder;
}


} } // namespace IoT::ZWave
