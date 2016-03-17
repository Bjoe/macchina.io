//
// SwitchBinaryServerHelper.h
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


#ifndef SwitchBinaryServerHelper_INCLUDED
#define SwitchBinaryServerHelper_INCLUDED


#include "IoT/Devices/ISwitchBinary.h"
#include "IoT/Devices/SwitchBinary.h"
#include "IoT/Devices/SwitchBinaryRemoteObject.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/ServerHelper.h"


namespace IoT {
namespace Devices {


class SwitchBinaryServerHelper
{
public:
	typedef IoT::Devices::SwitchBinary Service;

	SwitchBinaryServerHelper();
		/// Creates a SwitchBinaryServerHelper.

	~SwitchBinaryServerHelper();
		/// Destroys the SwitchBinaryServerHelper.

	static Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> createRemoteObject(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates and returns a RemoteObject wrapper for the given IoT::Devices::SwitchBinary instance.

	static void enableEvents(const std::string& uri, const std::string& protocol);
		/// Enables remote events for the RemoteObject identified by the given URI.
		///
		/// Events will be delivered using the Transport for the given protocol.
		/// Can be called multiple times for the same URI with different protocols.

	static std::string registerObject(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId);
		/// Creates a RemoteObject wrapper for the given IoT::Devices::SwitchBinary instance
		/// and registers it with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static std::string registerRemoteObject(Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> pRemoteObject, const std::string& listenerId);
		/// Registers the given RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener's ID.
		/// 
		///	Returns the URI created for the object.

	static void shutdown();
		/// Removes the Skeleton for IoT::Devices::SwitchBinary from the ORB.

	static void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB.

private:
	static Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid);

	void enableEventsImpl(const std::string& uri, const std::string& protocol);

	static SwitchBinaryServerHelper& instance();
		/// Returns a static instance of the helper class.

	std::string registerObjectImpl(Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> pRemoteObject, const std::string& listenerId);

	void registerSkeleton();

	void unregisterObjectImpl(const std::string& uri);

	void unregisterSkeleton();

	Poco::RemotingNG::ORB* _pORB;
};


inline Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> SwitchBinaryServerHelper::createRemoteObject(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return SwitchBinaryServerHelper::instance().createRemoteObjectImpl(pServiceObject, oid);
}


inline void SwitchBinaryServerHelper::enableEvents(const std::string& uri, const std::string& protocol)
{
	SwitchBinaryServerHelper::instance().enableEventsImpl(uri, protocol);
}


inline std::string SwitchBinaryServerHelper::registerObject(Poco::SharedPtr<IoT::Devices::SwitchBinary> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid, const std::string& listenerId)
{
	return SwitchBinaryServerHelper::instance().registerObjectImpl(createRemoteObject(pServiceObject, oid), listenerId);
}


inline std::string SwitchBinaryServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::SwitchBinaryRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SwitchBinaryServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


inline void SwitchBinaryServerHelper::unregisterObject(const std::string& uri)
{
	SwitchBinaryServerHelper::instance().unregisterObjectImpl(uri);
}


} // namespace Devices
} // namespace IoT


REMOTING_SPECIALIZE_SERVER_HELPER(IoT::Devices, SwitchBinary)


#endif // SwitchBinaryServerHelper_INCLUDED

