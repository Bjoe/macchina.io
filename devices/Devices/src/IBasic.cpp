//
// IBasic.cpp
//
// Package: Generated
// Module:  IBasic
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IBasic.h"


namespace IoT {
namespace Devices {


IBasic::IBasic():
	IoT::Devices::IDevice(),
	stateChanged()
{
}


IBasic::~IBasic()
{
}


bool IBasic::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IBasic::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Basic");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& IBasic::type() const
{
	return typeid(IBasic);
}


} // namespace Devices
} // namespace IoT

