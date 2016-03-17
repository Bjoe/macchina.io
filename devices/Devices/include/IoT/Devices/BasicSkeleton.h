//
// BasicSkeleton.h
//
// Package: Generated
// Module:  BasicSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef BasicSkeleton_INCLUDED
#define BasicSkeleton_INCLUDED


#include "IoT/Devices/BasicRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class BasicSkeleton: public Poco::RemotingNG::Skeleton
{
public:
	BasicSkeleton();
		/// Creates a BasicSkeleton.

	virtual ~BasicSkeleton();
		/// Destroys a BasicSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& BasicSkeleton::remoting__typeId() const
{
	return IBasic::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // BasicSkeleton_INCLUDED

