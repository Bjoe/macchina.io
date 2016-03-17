//
// Node.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_NODE_H
#define IOT_ZWAVE_NODE_H


#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/SharedPtr.h"
#include <map>
#include <string>
#include <vector>

#include "IoT/ZWave/BaseCommandClass.h"
#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {


class Node : public Poco::OSP::Service
{
public:
	static constexpr auto NAME = "ZWave node";
	static constexpr auto SYMBOLIC_NAME = "io.macchina.zwave.node";

	using Ptr = Poco::AutoPtr<Node>;

	Node(Way::Controller::Ptr controller, Way::NodeIdentifier nodeId);
	~Node() override = default;

	// Service interface
	const std::type_info& type() const override;
	bool isA(const std::type_info& otherType) const override;

	Way::NodeIdentifier id() const;

	bool isInterviewDone() const;
	Way::Error forceReInterview() const;
	Way::Error sendNop() const;
	Way::Error loadXml(const std::string& fileName);

	template <class C> Poco::SharedPtr<C> findCommandClass() const
	{
		Poco::SharedPtr<C> result;
		std::map<Way::CommandClassId, BaseCommandClass::Ptr>::const_iterator
			iter = commandClassList_.find(C::CLASS_ID);
		if (iter != commandClassList_.end())
		{
			result = (iter->second).cast<C>();
		}
		return result;
	}

	std::vector<Way::NodeInstance> getInstances() const;

	std::map<std::string, Way::DataHolder::Ptr> getDataHolders() const;
	std::map<std::string, Way::DataHolder::Ptr> getDataHoldersForInstance(Way::NodeInstance instance) const;
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> getCommandClasses() const;
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> getCommandClassesForInstance(Way::NodeInstance instance) const;

	void addInstance(Way::NodeInstance instance);
	void removeInstance(Way::NodeInstance instance);

	void addCommandClass(BaseCommandClass::Ptr command);
	void addCommandClass(
		Way::NodeInstance instance,
		BaseCommandClass::Ptr command);

	void removeCommandClass(Way::CommandClassId commandId);
	void removeCommandClass(
		Way::NodeInstance instance,
		Way::CommandClassId commandId);

private:
	Way::Controller::Ptr zWay_;
	Way::NodeIdentifier nodeId_;
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> commandClassList_ = {};
	std::map<Way::NodeInstance,	std::map<Way::CommandClassId, BaseCommandClass::Ptr>> instances_ = {};
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_NODE_H
