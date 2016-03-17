//
// BaseCommandClass.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_COMMANDCLASS_H
#define IOT_ZWAVE_COMMANDCLASS_H


#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"
#include <map>
#include <string>

#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {


class BaseCommandClass
{
public:
	using Ptr = Poco::SharedPtr<BaseCommandClass>;

	BaseCommandClass(
		Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId classId);
	virtual ~BaseCommandClass() = default;

	virtual Way::CommandClassId commandClassId() const = 0;
	virtual std::string commandClassName() const = 0;
	virtual Way::Error reportValue() const;
	virtual Poco::Dynamic::Var::Ptr getValue() const;
	virtual Way::DataHolder::Ptr getDataHolder() const;

	virtual Way::Error setValue(const Poco::Dynamic::Var& /*val*/);

	bool isInterviewDone() const;
	Way::Error runInterview() const;

protected:
	Way::Controller::Ptr controller_;
	Way::NodeIdentifier identifier_;
	Way::NodeInstance instance_;
	Way::CommandClassId classId_;
	std::map<std::string, Way::DataHolder::Ptr> dataHolders_;

	Poco::Dynamic::Var::Ptr getDataHolderValue(const std::string& dataHolderName) const;
	Way::DataHolder::Ptr getDataHolder(const std::string& dataHolderName) const;
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_COMMANDCLASS_H
