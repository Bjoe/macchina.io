//
// Service.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_SERVICE_H
#define IOT_ZWAVE_SERVICE_H


#include <typeinfo>

#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"

#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"

#include "IoT/ZWave/NodesManager.h"


namespace IoT {
namespace ZWave {


class Service : public Poco::OSP::Service
{
public:
	using Ptr = Poco::AutoPtr<Service>;
	static constexpr auto SERVICE_NAME = "IoT.ZWave.Service";

	Service(
		Way::Controller::Ptr controller,
		NodesManager::Ptr nodesServiceHandler);
	~Service() override = default;

	const std::type_info& type() const override;
	bool isA(const std::type_info& otherType) const override;

	Way::Error resetControllerToFactoryDefault();
	Way::Error inclusionMode(bool on);
	Way::Error exclusionMode(bool on);

private:
	Way::Controller::Ptr controller_;
	NodesManager::Ptr nodesServiceHandler_;
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_SERVICE_HPP
