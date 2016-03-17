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


#ifndef IOT_ZWAVE_WAY_COMMANDCLASS_SWITCHBINARY_H
#define IOT_ZWAVE_WAY_COMMANDCLASS_SWITCHBINARY_H


#include "IoT/ZWave/Way/Error.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "Poco/Dynamic/Var.h"


namespace IoT {
namespace ZWave {
namespace Way {
namespace CommandClass {


class SwitchBinary
{
public:
	SwitchBinary(Controller::Ptr controller);

	Error get(NodeIdentifier identifier, NodeInstance instance);
	Error set(NodeIdentifier identifier, NodeInstance instance, const Poco::Dynamic::Var& val);

private:
	Controller::Ptr controller_;
};


} } } }


#endif // IOT_ZWAVE_WAY_COMMANDCLASS_SWITCHBINARY_H
