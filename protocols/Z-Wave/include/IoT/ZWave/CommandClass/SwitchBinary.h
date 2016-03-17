//
// SwitchBinary.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_COMMANDCLASS_SWITCHBINARY_H
#define IOT_ZWAVE_COMMANDCLASS_SWITCHBINARY_H


#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"

#include "IoT/ZWave/BaseCommandClass.h"
#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {
namespace CommandClass {


class SwitchBinary : public IoT::ZWave::BaseCommandClass
{
public:
	using Ptr = Poco::SharedPtr<SwitchBinary>;
	static constexpr Way::CommandClassId CLASS_ID = 0x25;

	SwitchBinary(
		Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance);
	~SwitchBinary() override = default;

	Way::Error setOn();
	Way::Error setOff();
	bool isOn() const;
	bool isOff() const;

	// BaseCommandClass interface
	Way::CommandClassId commandClassId() const override;
	std::string commandClassName() const override;

	Way::Error reportValue() const override;
	Poco::Dynamic::Var::Ptr getValue() const override;
	Way::DataHolder::Ptr getDataHolder() const override;

	Way::Error setValue(const Poco::Dynamic::Var& val) override;
};


} } } // namespace IoT::ZWave::CommandClass


#endif // IOT_ZWAVE_COMMANDCLASS_SWITCHBINARY_H
