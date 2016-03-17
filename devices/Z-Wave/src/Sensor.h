//
// Sensor.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DEVICES_SENSOR_HPP
#define IOT_ZWAVE_DEVICES_SENSOR_HPP


#include <string>

#include "Poco/Any.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Logger.h"
#include "Poco/SharedPtr.h"

#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/Devices/Sensor.h"

#include "IoT/ZWave/Way/DataHolderEvent.h"
#include "IoT/ZWave/Scale.h"


namespace IoT {
namespace ZWave {
namespace Devices {


class Sensor : public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, IoT::ZWave::Devices::Sensor>
{
public:
	constexpr static const auto NAME = "Zwave sensor";
	constexpr static const auto SYMBOLIC_NAME = "io.macchina.zwave.sensor";

	Sensor(Poco::Any deviceIdentifire,
		Poco::Logger& log,
		IoT::ZWave::Scale::Ptr scale);
	virtual ~Sensor();

	// IoT::Devices::Sensor
	virtual double value() const;
	virtual bool ready() const;

protected:
	Poco::Any getName(const std::string& /*unused*/) const;
	Poco::Any getSymbolicName(const std::string& /*unused*/) const;
	Poco::Any getDeviceIdentifier(const std::string& /*unused*/) const;
	Poco::Any getDisplayValue(const std::string& /*unused*/) const;
	Poco::Any getPhysicalQuantity(const std::string& /*unused*/) const;
	Poco::Any getPhysicalUnit(const std::string& /*unused*/) const;

	void update(const void* /*pSender*/, Poco::Dynamic::Var::Ptr& value);

private:
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<const double>> eventPolicy_ = new IoT::Devices::NoModerationPolicy<const double>(valueChanged);
	Way::DataHolderEvent::Ptr dataEvent_ = nullptr;
	Poco::Any deviceIdentifier_;
	Poco::Logger& log_;
	IoT::ZWave::Scale::Ptr scale_;
};


} } } // namespace IoT::ZWave::Devices


#endif // IOT_ZWAVE_DEVICES_SENSOR_HPP
