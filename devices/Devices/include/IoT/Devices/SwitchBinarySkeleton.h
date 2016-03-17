//
// SwitchBinarySkeleton.h
//
// Package: Generated
// Module:  SwitchBinarySkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef SwitchBinarySkeleton_INCLUDED
#define SwitchBinarySkeleton_INCLUDED


#include "IoT/Devices/SwitchBinaryRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class SwitchBinarySkeleton: public Poco::RemotingNG::Skeleton
{
public:
	SwitchBinarySkeleton();
		/// Creates a SwitchBinarySkeleton.

	virtual ~SwitchBinarySkeleton();
		/// Destroys a SwitchBinarySkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchBinarySkeleton::remoting__typeId() const
{
	return ISwitchBinary::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // SwitchBinarySkeleton_INCLUDED

