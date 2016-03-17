//
// ConnadClassFactory.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_COMMANDCLASSFACTORY_H
#define IOT_ZWAVE_COMMANDCLASSFACTORY_H


#include "IoT/ZWave/BaseCommandClass.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {


class CommandClassFactory
{
public:
	static BaseCommandClass::Ptr create(const Way::Controller::Ptr& controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId commandId);

private:
	CommandClassFactory() = default;
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_COMMANDCLASSFACTORY_H
