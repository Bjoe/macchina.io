//
// Scale.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_SCALE_H
#define IOT_ZWAVE_SCALE_H


#include <map>
#include <string>

#include "Poco/SharedPtr.h"

#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {


class Scale
{
public:
	using Ptr = Poco::SharedPtr<Scale>;

	enum SensorType
	{
		UNKNOWN_SENSORTYPE = -1,
		ELECTRIC = 10,
		GAS = 20,
		WATER = 30
	};

	enum Type
	{
		UNKNOWN_SCALE = -1,

		// sensorType = 1 -> sensorTypeString = Electric
		KWH = 10,
		KVAH = 11,
		W = 12,
		PULSE_COUNT_E = 13,
		V = 14,
		A = 15,
		POWER_FACTOR = 16,

		// sensorType = 2 -> sensorTypeString = Gas
		CUBIC_METER_G = 20,
		CUBIC_FEET_G = 21,
		RESERVED_G = 23,
		PULSE_COUNT_G = 24,

		// sensorType = 3 -> sensorTypeString = Water
		CUBIC_METER_W = 31,
		CUBIC_FEET_W = 32,
		US_GALLON_W = 33,
		PULSE_COUNT_W = 34
	};

	Scale(
		Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		std::string dataPath,
		std::map<std::string, Way::DataHolder::Ptr> sensorDataHolders);

	virtual ~Scale() = default;

	SensorType getSensorType() const;
	std::string getSensorName() const;

	Type getType() const;
	std::string getName() const;

	Way::Error reportValue() const;
	double getValue() const;

	Way::DataHolder::Ptr getDataHolder() const;

private:
	Way::Controller::Ptr zWay_;
	Way::NodeIdentifier identifier_;
	Way::NodeInstance instance_;
	std::string dataPath_;
	std::map<std::string, Way::DataHolder::Ptr> sensorDataHolders_;

	Way::DataHolder::Ptr getDataHolder(const std::string& name) const;
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_SCALE_H
