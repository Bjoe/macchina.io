//
// DataHolder.h
//
// $Id$
//
// Copyright (c) 2016, Joerg-Christian Boehme.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IOT_ZWAVE_DATAHOLDER_H
#define IOT_ZWAVE_DATAHOLDER_H


#include "Poco/Dynamic/Var.h"
#include "Poco/SharedPtr.h"

#include "IoT/ZWave/Way/DataHolderEvent.h"
#include "IoT/ZWave/Way/Controller.h"


namespace IoT {
namespace ZWave {
namespace Way {


class DataHolder
{
public:
	using Ptr = Poco::SharedPtr<DataHolder>;
	virtual ~DataHolder() = default;

	Poco::Dynamic::Var::Ptr getValue() const;

	IoT::ZWave::Way::DataHolderEvent::Ptr createDataChangeEvent();

protected:
	virtual Poco::Dynamic::Var::Ptr getValueFromDataHolder() const = 0;
	virtual IoT::ZWave::Way::DataHolderEvent::Ptr createInstance() = 0;
};


} } } // namespace IoT::ZWave::Way


#endif // IOT_ZWAVE_DATAHOLDER_H
