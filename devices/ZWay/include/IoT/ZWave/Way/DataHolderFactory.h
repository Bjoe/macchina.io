//
// DataHolderFactory.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DATAHOLDERFACTORY_H
#define IOT_ZWAVE_DATAHOLDERFACTORY_H


#include <map>
#include <string>

#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {
namespace Way {


class DataHolderFactory
{
public:
	static std::map<std::string, DataHolder::Ptr> createDeviceDataHolders(Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier);

	static std::map<std::string, DataHolder::Ptr> createInstanceDataHolders(Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance);

	static std::map<std::string, DataHolder::Ptr> createCommandClassHolders(Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId classId);

	static std::map<std::string, DataHolder::Ptr> searchAndCreateCommandClassHolders(
		Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId classId,
		const std::string& dataPath);

	static DataHolder::Ptr searchAndCreateCommandClassHolder(Way::Controller::Ptr controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId classId,
		const std::string& dataPath);

private:
	DataHolderFactory() = default;
};


} } } // namespace IoT::ZWave::Way


#endif // IOT_ZWAVE_DATAHOLDERFACTORY_H
