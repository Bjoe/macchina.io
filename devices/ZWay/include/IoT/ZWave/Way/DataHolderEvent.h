//
// DataHolderEvent.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DATAHOLDEREVENT_H
#define IOT_ZWAVE_DATAHOLDEREVENT_H


#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Dynamic/Var.h"

#include "IoT/ZWave/Way/Controller.h"
#include "IoT/ZWave/Way/Error.h"


namespace IoT {
namespace ZWave {
namespace Way {


class DataHolderEvent
{
public:
	using Ptr = Poco::SharedPtr<IoT::ZWave::Way::DataHolderEvent>;
	Poco::BasicEvent<Poco::Dynamic::Var::Ptr> event_;

	DataHolderEvent(Way::Controller::Ptr controller);
	virtual ~DataHolderEvent() = default;

	Way::Error registerDataChangeEvent();
	Way::Error unregisterDataChangeEvent();

	void notify(Poco::Dynamic::Var::Ptr data);

protected:
	virtual Way::Error registerEvent() = 0;
	virtual Way::Error unregisterEvent() = 0;
private:
	Way::Controller::Ptr controller_;
};


} } } // namespace Iot::ZWave::Way


#endif // IOT_ZWAVE_DATAHOLDEREVENT_H
