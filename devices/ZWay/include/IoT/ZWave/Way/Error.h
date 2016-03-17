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


#ifndef IOT_ZWAVE_ERROR_H
#define IOT_ZWAVE_ERROR_H


#include <string>


namespace IoT {
namespace ZWave {
namespace Way {


class Error
{
public:
	Error() = default;
	Error(std::string errorMessage, int state);
	virtual ~Error() = default;

	bool isError() const;
	bool isNoError() const;
	std::string errorMessage() const;

private:
	int state_ = 0;
	std::string errorMessage_ = {};
};


} } } // namespace IoT::ZWave::Device


#endif // IOT_ZWAVE_ERROR_H
