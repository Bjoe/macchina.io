//
// IBasic.h
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


#ifndef IBasic_INCLUDED
#define IBasic_INCLUDED


#include "IoT/Devices/Basic.h"
#include "IoT/Devices/IDevice.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IBasic: public IoT::Devices::IDevice
{
public:
	typedef Poco::AutoPtr<IBasic> Ptr;

	IBasic();
		/// Creates a IBasic.

	virtual ~IBasic();
		/// Destroys the IBasic.

	virtual int get() const = 0;

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void set(int value) = 0;

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const int > stateChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IBasic_INCLUDED

