//
// Controller.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_WAY_ZWAYCONTROLLER_HPP
#define IOT_ZWAVE_WAY_ZWAYCONTROLLER_HPP


#include "IoT/ZWave/Way/Controller.h"
#include "ZDefsPublic.h"


namespace IoT {
namespace ZWave {
namespace Way {

class ZWayController : public Controller
{
public:
	static ZWay convert(const IoT::ZWave::Way::Controller* controller);

	ZWayController(ZWay zway);

	ZWay instance() const;

private:
	ZWay zWay_;
};


} } }


#endif // IOT_ZWAVE_WAY_ZWAYCONTROLLER_HPP
