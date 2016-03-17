//
// ZWayDataHolderEvent.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_ZWAYDATAHOLDEREVENT_H
#define IOT_ZWAVE_ZWAYDATAHOLDEREVENT_H


#include "IoT/ZWave/Way/DataHolderEvent.h"
#include "IoT/ZWave/Way/Error.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Dynamic/Var.h"
#include "ZData.h"


namespace IoT {
namespace ZWave {
namespace Way {


class ZWayDataHolderEvent : public DataHolderEvent
{
public:
	using DataHolderEvent::DataHolderEvent;

	void setData(ZDataHolder data);

protected:
	Way::Error registerEvent() override;
	Way::Error unregisterEvent() override;
private:
	ZDataHolder data_ = NULL;
};


} } } // namespace Iot::ZWave::Way


#endif // IOT_ZWAVE_ZWAYDATAHOLDEREVENT_H
