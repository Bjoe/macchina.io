//
// Event.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DEVICEEVENT_H
#define IOT_ZWAVE_DEVICEEVENT_H


#include "IoT/ZWave/Way/Defs.h"


namespace IoT {
namespace ZWave {
namespace Way {


class Event
{
public:
	enum Type {
		Unknown = 0x00,
		DeviceAdded = 0x01,
		DeviceRemoved = 0x02,
		InstanceAdded = 0x04,
		InstanceRemoved = 0x08,
		CommandAdded = 0x10,
		CommandRemoved = 0x20
	};

	explicit Event(
		Type eventType,
		NodeIdentifier nodeId,
		NodeInstance instanceId = 0,
		CommandClassId commandClass = 0);

	Type eventType() const;
	NodeIdentifier nodeId() const;
	NodeInstance instanceId() const;
	CommandClassId commandClass() const;

private:
	Type eventType_;
	NodeIdentifier nodeId_;
	NodeInstance instanceId_;
	CommandClassId commandClass_;
};


} } } // namespace IoT::ZWave::Device


#endif // IOT_ZWAVE_DEVICEEVENT_H
