//
// Basic.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DEVICES_BASIC_H
#define IOT_ZWAVE_DEVICES_BASIC_H


#include "IoT/Devices/Basic.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/ZWave/CommandClass/Basic.h"
#include "IoT/ZWave/Way/DataHolderEvent.h"
#include "Poco/Logger.h"
#include "Poco/SharedPtr.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/Any.h"
#include <string>

namespace IoT {
namespace ZWave {
namespace Devices {


class Basic : public IoT::Devices::DeviceImpl<IoT::Devices::Basic, Basic>
{
public:
    static constexpr auto NAME = "ZWave basic";
    static constexpr auto SYMBOLIC_NAME = "io.macchina.zwave.basic";

    Basic(
        Poco::Any deviceIdentifier,
        Poco::Logger& logger,
        IoT::ZWave::CommandClass::Basic::Ptr basic);
    virtual ~Basic();

    virtual void set(int value);
    virtual int get() const;

protected:
    Poco::Any getName(const std::string& /*unused*/) const;
    Poco::Any getSymbolicName(const std::string& /*unused*/) const;
    Poco::Any getDeviceIdentifier(const std::string& /*unused*/) const;
    Poco::Any getDisplayValue(const std::string& /*unused*/) const;

    void update(const void* /*pSender*/, Poco::Dynamic::Var::Ptr& value);

private:
    Poco::SharedPtr<IoT::Devices::EventModerationPolicy<const int>> eventPolicy_ = new IoT::Devices::NoModerationPolicy<const int>(stateChanged);
    Way::DataHolderEvent::Ptr dataEvent_ = nullptr;
    Poco::Any deviceIdentifier_;
    Poco::Logger& logger_;
    IoT::ZWave::CommandClass::Basic::Ptr basic_;

    void logging(const Way::Error& error);
};


} } } // namespace Devices


#endif // IOT_ZWAVE_DEVICES_BASIC_H
