//
// SwitchBinaryServerHelper.cpp
//
// Package: Generated
// Module:  SwitchBinaryServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SwitchBinaryServerHelper.h"
#include "IoT/Devices/SwitchBinaryEventDispatcher.h"
#include "IoT/Devices/SwitchBinarySkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<SwitchBinaryServerHelper> shSwitchBinaryServerHelper;
}


SwitchBinaryServerHelper::SwitchBinaryServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


SwitchBinaryServerHelper::~SwitchBinaryServerHelper()
{
}


void SwitchBinaryServerHelper::shutdown()
{
	SwitchBinaryServerHelper::instance().unregisterSkeleton();
	shSwitchBinaryServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> SwitchBinaryServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new SwitchBinaryRemoteObject(oid, pServiceObject);
}


void SwitchBinaryServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<SwitchBinaryRemoteObject> pRemoteObject = pIdentifiable.cast<SwitchBinaryRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


SwitchBinaryServerHelper& SwitchBinaryServerHelper::instance()
{
	return *shSwitchBinaryServerHelper.get();
}


std::string SwitchBinaryServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void SwitchBinaryServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.SwitchBinary", new SwitchBinarySkeleton);
}


void SwitchBinaryServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void SwitchBinaryServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.SwitchBinary", true);
}


} // namespace Devices
} // namespace IoT

