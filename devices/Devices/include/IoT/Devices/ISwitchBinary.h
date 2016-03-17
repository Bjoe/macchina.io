//
// ISwitchBinary.h
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


#ifndef ISwitchBinary_INCLUDED
#define ISwitchBinary_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/SwitchBinary.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ISwitchBinary: public IoT::Devices::IDevice
{
public:
	typedef Poco::AutoPtr<ISwitchBinary> Ptr;

	ISwitchBinary();
		/// Creates a ISwitchBinary.

	virtual ~ISwitchBinary();
		/// Destroys the ISwitchBinary.

	virtual bool get() const = 0;

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

	virtual void setOff() = 0;

	virtual void setOn() = 0;

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const bool > stateChanged;
};


} // namespace Devices
} // namespace IoT


#endif // ISwitchBinary_INCLUDED

