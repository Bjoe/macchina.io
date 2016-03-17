//
// ISwitchBinary.cpp
//
// Package: Generated
// Module:  ISwitchBinary
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/ISwitchBinary.h"


namespace IoT {
namespace Devices {


ISwitchBinary::ISwitchBinary():
	IoT::Devices::IDevice(),
	stateChanged()
{
}


ISwitchBinary::~ISwitchBinary()
{
}


bool ISwitchBinary::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& ISwitchBinary::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("IoT.Devices.SwitchBinary");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& ISwitchBinary::type() const
{
	return typeid(ISwitchBinary);
}


} // namespace Devices
} // namespace IoT

