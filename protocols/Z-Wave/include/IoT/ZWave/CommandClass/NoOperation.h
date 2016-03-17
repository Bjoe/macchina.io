//
// NoOperation.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_COMMANDCLASS_NOOPERATION_H
#define IOT_ZWAVE_COMMANDCLASS_NOOPERATION_H


#include "IoT/ZWave/BaseCommandClass.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


class NoOperation : public BaseCommandClass
{
public:
	using Ptr = Poco::SharedPtr<NoOperation>;
	static constexpr Way::CommandClassId CLASS_ID = 0x00;

	NoOperation(
		Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance);
	~NoOperation() override = default;

	// BaseCommandClass interface
	Way::CommandClassId commandClassId() const override;
	std::string commandClassName() const override;
};


} } } // namespace IoT::ZWave::CommandClass


#endif // IOT_ZWAVE_COMMANDCLASS_NOOPERATION_H
