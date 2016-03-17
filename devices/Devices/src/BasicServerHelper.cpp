//
// BasicServerHelper.cpp
//
// Package: Generated
// Module:  BasicServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/BasicServerHelper.h"
#include "IoT/Devices/BasicEventDispatcher.h"
#include "IoT/Devices/BasicSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<BasicServerHelper> shBasicServerHelper;
}


BasicServerHelper::BasicServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


BasicServerHelper::~BasicServerHelper()
{
}


void BasicServerHelper::shutdown()
{
	BasicServerHelper::instance().unregisterSkeleton();
	shBasicServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::BasicRemoteObject> BasicServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new BasicRemoteObject(oid, pServiceObject);
}


void BasicServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<BasicRemoteObject> pRemoteObject = pIdentifiable.cast<BasicRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


BasicServerHelper& BasicServerHelper::instance()
{
	return *shBasicServerHelper.get();
}


std::string BasicServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::BasicRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void BasicServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Basic", new BasicSkeleton);
}


void BasicServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void BasicServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Basic", true);
}


} // namespace Devices
} // namespace IoT

