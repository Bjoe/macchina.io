//
// IBinarySwitch.cpp
//
// Package: Generated
// Module:  IBinarySwitch
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IBinarySwitch.h"


namespace IoT {
namespace Devices {


IBinarySwitch::IBinarySwitch():
	IoT::Devices::IDevice(),
	stateChanged()
{
}


IBinarySwitch::~IBinarySwitch()
{
}


const Poco::RemotingNG::Identifiable::TypeId& IBinarySwitch::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("BinarySwitch");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


} // namespace Devices
} // namespace IoT

