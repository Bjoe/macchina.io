//
// BasicRemoteObject.cpp
//
// Package: Generated
// Module:  BasicRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/BasicRemoteObject.h"
#include "IoT/Devices/BasicEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


BasicRemoteObject::BasicRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Basic> pServiceObject):
	IoT::Devices::IBasic(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &BasicRemoteObject::event__stateChanged);
}


BasicRemoteObject::~BasicRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &BasicRemoteObject::event__stateChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BasicRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void BasicRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new BasicEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool BasicRemoteObject::remoting__hasEvents() const
{
	return true;
}


void BasicRemoteObject::event__stateChanged(const int& data)
{
	stateChanged(this, data);
}


} // namespace Devices
} // namespace IoT

