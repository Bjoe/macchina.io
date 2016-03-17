//
// SwitchBinaryRemoteObject.cpp
//
// Package: Generated
// Module:  SwitchBinaryRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SwitchBinaryRemoteObject.h"
#include "IoT/Devices/SwitchBinaryEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SwitchBinaryRemoteObject::SwitchBinaryRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject):
	IoT::Devices::ISwitchBinary(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &SwitchBinaryRemoteObject::event__stateChanged);
}


SwitchBinaryRemoteObject::~SwitchBinaryRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &SwitchBinaryRemoteObject::event__stateChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SwitchBinaryRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SwitchBinaryRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SwitchBinaryEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SwitchBinaryRemoteObject::remoting__hasEvents() const
{
	return true;
}


void SwitchBinaryRemoteObject::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


} // namespace Devices
} // namespace IoT

