//
// BasicServerHelper.h
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


#ifndef BasicServerHelper_INCLUDED
#define BasicServerHelper_INCLUDED


#include "IoT/Devices/Basic.h"
#include "IoT/Devices/BasicRemoteObject.h"
#include "IoT/Devices/IBasic.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class BasicServerHelper
{
public:
	typedef IoT::Devices::Basic Service;

	BasicServerHelper();
		/// Creates a BasicServerHelper.

	~BasicServerHelper();
		/// Destroys the BasicServerHelper.

	static Poco::AutoPtr<IoT::Devices::BasicRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::Basic instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::Basic instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::BasicRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::Basic from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::BasicRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static BasicServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::BasicRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::BasicRemoteObject> BasicServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return BasicServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void BasicServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	BasicServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string BasicServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::Basic> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return BasicServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string BasicServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::BasicRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return BasicServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void BasicServerHelper::unregisterObject(const std::string& uri)
{
	BasicServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, Basic)


#endif // BasicServerHelper_INCLUDED

