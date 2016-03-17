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


#ifndef IOT_DEVICES_SWITCHBINARY_H
#define IOT_DEVICES_SWITCHBINARY_H


#include "IoT/Devices/Device.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API SwitchBinary : public Device
{
public:
	Poco::BasicEvent<const bool> stateChanged;

	SwitchBinary();
	~SwitchBinary();

	virtual void setOn() = 0;
	virtual void setOff() = 0;
	virtual bool get() const = 0;
};


} } // namespace IoT::Devices


#endif // IOT_DEVICES_SWITCHBINARY_H
