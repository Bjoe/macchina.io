//
// Error.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_ZWAYERROR_H
#define IOT_ZWAVE_ZWAYERROR_H


#include "IoT/ZWave/Way/Error.h"
#include "ZErrors.h"
#include <string>


namespace IoT {
namespace ZWave {
namespace Way {


class ZWayError
{
public:
	ZWayError() = default;
	ZWayError(std::string errorMessage);
	ZWayError(std::string errorMessage, ZWError zWError);
	virtual ~ZWayError() = default;

	Error error() const;
private:
	ZWError zWError_ = {};
	std::string errorMessage_ = {};
};


} } } // namespace IoT::ZWave::Device


#endif // IOT_ZWAVE_ZWAYERROR_H
