//
// SwitchBinaryEventDispatcher.h
//
// Package: Generated
// Module:  SwitchBinaryEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef SwitchBinaryEventDispatcher_INCLUDED
#define SwitchBinaryEventDispatcher_INCLUDED


#include "IoT/Devices/SwitchBinaryRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class SwitchBinaryEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	SwitchBinaryEventDispatcher(SwitchBinaryRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a SwitchBinaryEventDispatcher.

	virtual ~SwitchBinaryEventDispatcher();
		/// Destroys the SwitchBinaryEventDispatcher.

	void event__stateChanged(const void* pSender, const bool& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const bool& data);

	static const std::string DEFAULT_NS;
	SwitchBinaryRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchBinaryEventDispatcher::remoting__typeId() const
{
	return ISwitchBinary::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // SwitchBinaryEventDispatcher_INCLUDED

