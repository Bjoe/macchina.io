//
// DataUtil.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_WAY_DATAUTIL_HPP
#define IOT_ZWAVE_WAY_DATAUTIL_HPP


#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "Poco/Dynamic/Var.h"
#include "ZDefsPublic.h"

#include <string>

namespace IoT {
namespace ZWave {
namespace Way {


class DataUtil
{
public:
	static ZDataHolder findDeviceData(
			ZWay zway,
			NodeIdentifier identifier,
			const std::string& path);
	static ZDataHolder findInstanceData(
			ZWay zway,
			NodeIdentifier identifier,
			NodeInstance instance,
			const std::string& path);
	static ZDataHolder findCommandClassData(
			ZWay zway,
			NodeIdentifier identifier,
			NodeInstance instance,
			CommandClassId classId,
			const std::string& path);

	static Poco::Dynamic::Var::Ptr getDataValue(ZDataHolder data);


private:
	DataUtil() = default;
};


} } } // namespace IoT::ZWave::Way

#endif // IOT_ZWAVE_WAY_DATAUTIL_HPP
