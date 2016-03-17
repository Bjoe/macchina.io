#include "IoT/ZWave/Scales.h"

#include <stdexcept>
#include <string>

#include "Poco/NumberParser.h"

#include "IoT/ZWave/Way/DataHolderFactory.h"

#include <utility>

namespace IoT {
namespace ZWave {


Scales Scales::createInstance(const Way::Controller::Ptr& controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId,
	std::map<std::string, Way::DataHolder::Ptr> dataHolders)
{
	std::map<Scale::Type, Scale::Ptr> scales;
	for (auto& iter : dataHolders)
	{
		std::string dataPath = iter.first;
		int value = 0;
		if (Poco::NumberParser::tryParse(dataPath, value))
		{
			std::map<std::string, Way::DataHolder::Ptr> sensorDataHolders =
				Way::DataHolderFactory::searchAndCreateCommandClassHolders(
					controller,
					identifier,
					instance,
					classId,
					dataPath);

			Scale::SensorType sensorType = Scale::UNKNOWN_SENSORTYPE;
			auto dataHolderPair = sensorDataHolders.find(dataPath + ".sensorType");
			if (dataHolderPair != sensorDataHolders.cend())
			{
				Way::DataHolder::Ptr sensorTypeHolder = dataHolderPair->second;
				Poco::Dynamic::Var::Ptr sensorTypeVar =	sensorTypeHolder->getValue();
				if (!sensorTypeVar->isEmpty())
				{
					int type = sensorTypeVar->convert<int>();
					type *= 10;
					sensorType = static_cast<Scale::SensorType>(type);
				}
			}

			int scaleValue = -1;
			dataHolderPair = sensorDataHolders.find(dataPath + ".scale");
			if (dataHolderPair != sensorDataHolders.cend())
			{
				Way::DataHolder::Ptr scaleTypeHolder = dataHolderPair->second;
				Poco::Dynamic::Var::Ptr scaleTypeVar = scaleTypeHolder->getValue();
				if (!scaleTypeVar->isEmpty())
				{
					scaleValue = scaleTypeVar->convert<int>();
				}
			}

			if (scaleValue > 0 && sensorType > 0)
			{
				int result = sensorType + scaleValue;
				Scale::Type scaleType = static_cast<Scale::Type>(result);
				scales[scaleType] = new Scale(controller, identifier, instance, dataPath, sensorDataHolders);
			}
		}
	}
	return Scales(scales);
}

std::map<Scale::Type, Scale::Ptr> Scales::getScales() const { return scales_; }

Scales::Scales(std::map<Scale::Type, Scale::Ptr> scales) : scales_(std::move(scales)) {}


} } // namespace IoT::ZWave
