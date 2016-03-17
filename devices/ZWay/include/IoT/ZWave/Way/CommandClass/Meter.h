//
// Meter.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_WAY_COMMANDCLASS_METER_H
#define IOT_ZWAVE_WAY_COMMANDCLASS_METER_H


#include "IoT/ZWave/Way/Error.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace CommandClass {


class Meter
{
public:
	Meter(Controller::Ptr controller);

	Error get(NodeIdentifier identifier, NodeInstance instance, int scale);

private:
	Controller::Ptr controller_;
};


} } } }


#endif // IOT_ZWAVE_WAY_COMMANDCLASS_METER_H
