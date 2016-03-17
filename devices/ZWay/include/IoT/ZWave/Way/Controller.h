//
// Controller.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_WAY_CONTROLLER_H
#define IOT_ZWAVE_WAY_CONTROLLER_H


#include "Poco/SharedPtr.h"
#include "Poco/Tuple.h"
#include <map>

#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {
namespace Way {


class Controller
{
public:
	using Ptr = Poco::SharedPtr<Controller>;

	~Controller() = default;

	bool isInterviewiDone(NodeIdentifier identifier) const;
	Error forceDeviceInterview(NodeIdentifier identifier) const;
	Error runCommandClassInterview(
		NodeIdentifier identifier,
		NodeInstance instance,
		CommandClassId classId) const;

	Error sendDeviceNop(NodeIdentifier identifier) const;
	Error loadXmlForDevice(NodeIdentifier identifier, const std::string& fileName) const;
	void deviceAwakeQueue(NodeIdentifier identifier);

	Error resetToFactoryDefault();
	Error inclusionMode(bool on);
	Error exclusionMode(bool on);

	Error error() const;
};


} } } // namespace IoT::ZWave::Way


#endif // IOT_ZWAVE_WAY_CONTROLLER_H
