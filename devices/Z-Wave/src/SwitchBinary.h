//
// SwitchBinary.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DEVICES_SWITCHBINARY_H
#define IOT_ZWAVE_DEVICES_SWITCHBINARY_H


#include <string>

#include "Poco/Any.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Logger.h"
#include "Poco/SharedPtr.h"

#include "IoT/ZWave/Way/Error.h"

#include "IoT/ZWave/CommandClass/SwitchBinary.h"
#include "IoT/ZWave/Way/DataHolderEvent.h"

#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/Devices/SwitchBinary.h"


namespace IoT {
namespace ZWave {
namespace Devices {


class SwitchBinary : public IoT::Devices::DeviceImpl<IoT::Devices::SwitchBinary, SwitchBinary>
{
public:
	static constexpr auto NAME = "ZWave binary switch";
	static constexpr auto SYMBOLIC_NAME = "io.macchina.zwave.switchbinary";

	SwitchBinary(
		Poco::Any deviceIdentifier,
		Poco::Logger& log,
		IoT::ZWave::CommandClass::SwitchBinary::Ptr switchBinary);
	virtual ~SwitchBinary();

	virtual void setOn();
	virtual void setOff();
	virtual bool get() const;

protected:
	Poco::Any getName(const std::string& /*unused*/) const;
	Poco::Any getSymbolicName(const std::string& /*unused*/) const;
	Poco::Any getDeviceIdentifier(const std::string& /*unused*/) const;
	Poco::Any getDisplayValue(const std::string& /*unused*/) const;

	void update(const void* /*pSender*/, Poco::Dynamic::Var::Ptr& state);

private:
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<const bool>> eventPolicy_ = new IoT::Devices::NoModerationPolicy<const bool>(stateChanged);
	Way::DataHolderEvent::Ptr dataEvent_ = nullptr;
	Poco::Any deviceIdentifier_;
	Poco::Logger& log_;
	IoT::ZWave::CommandClass::SwitchBinary::Ptr switchBinary_;

	void logging(const Way::Error& error);
};


} } } // namespace IoT::Zwave::Devices


#endif // IOT_ZWAVE_DEVICES_SWITCHBINARY_H
