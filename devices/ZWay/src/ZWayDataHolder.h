//
// ZWayDataHolder.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_ZWAYDATAHOLDER_H
#define IOT_ZWAVE_ZWAYDATAHOLDER_H


#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"
#include "Poco/Tuple.h"
#include "ZData.h"

#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/DataHolderEvent.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {
namespace Way {


class ZWayDataHolder : public DataHolder
{
public:
	using DataHolder::DataHolder;
	ZWayDataHolder(Way::Controller::Ptr controller);

	void setData(ZDataHolder data);

protected:
	Poco::Dynamic::Var::Ptr getValueFromDataHolder() const override;
	IoT::ZWave::Way::DataHolderEvent::Ptr createInstance() override;
private:
	Way::Controller::Ptr controller_;
	ZDataHolder data_ = NULL;
};


} } } // namespace IoT::ZWave::Way


#endif // IOT_ZWAVE_ZWAYDATAHOLDER_H
