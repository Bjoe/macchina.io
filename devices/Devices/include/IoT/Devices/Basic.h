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


#ifndef IOT_DEVICES_BASIC_H
#define IOT_DEVICES_BASIC_H


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Basic : public Device
{
public:
    Poco::BasicEvent<const int> stateChanged;

    Basic();
    ~Basic();

    virtual void set(int value) = 0;
    virtual int get() const = 0;
};


} } // namespace IoT::Devices


#endif // IOT_DEVICES_BASIC_H
