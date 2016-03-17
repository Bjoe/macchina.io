//
// Scales.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_SCALES_H
#define IOT_ZWAVE_SCALES_H


#include <map>

#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Scale.h"
#include "IoT/ZWave/Way/Defs.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {


class Scales
{
public:
	static Scales createInstance(
		const Way::Controller::Ptr& controller,
		Way::NodeIdentifier identifier,
		Way::NodeInstance instance,
		Way::CommandClassId classId,
		std::map<std::string, Way::DataHolder::Ptr> dataHolders);

	std::map<Scale::Type, Scale::Ptr> getScales() const;

private:
	std::map<Scale::Type, Scale::Ptr> scales_;

	explicit Scales(std::map<Scale::Type, Scale::Ptr> scales);
};


} } // namespace IoT::ZWave


#endif // IOT_ZWAVE_SCALES_H
