//
// BasicEventDispatcher.h
//
// Package: Generated
// Module:  BasicEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BasicEventDispatcher_INCLUDED
#define BasicEventDispatcher_INCLUDED


#include "IoT/Devices/BasicRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Devices {


class BasicEventDispatcher: public Poco::RemotingNG::EventDispatcher
{
public:
	BasicEventDispatcher(BasicRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a BasicEventDispatcher.

	virtual ~BasicEventDispatcher();
		/// Destroys the BasicEventDispatcher.

	void event__stateChanged(const void* pSender, const int& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__stateChangedImpl(const std::string& subscriberURI, const int& data);

	static const std::string DEFAULT_NS;
	BasicRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BasicEventDispatcher::remoting__typeId() const
{
	return IBasic::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // BasicEventDispatcher_INCLUDED

