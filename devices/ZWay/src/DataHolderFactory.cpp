#include "IoT/ZWave/Way/DataHolderFactory.h"

#include "DataUtil.h"
#include "ZWayController.h"
#include "ZWayDataHolder.h"
#include "Poco/StringTokenizer.h"
#include "ZData.h"
#include <iostream>


namespace IoT {
namespace ZWave {
namespace Way {
namespace {


std::string getPathVariable(ZDataHolder data)
{
	char *path = zdata_get_path(data);
	std::string p(path);
	// devices.1.data.SDK -> SDK
	Poco::StringTokenizer tokenizer(p, ".");
	std::size_t index = tokenizer.find("data") + 1;
	auto itr = tokenizer.begin();
	itr += index;
	std::string var = (*itr++);
	while (itr != tokenizer.end())
	{
		var.append(".");
		var.append((*itr++));
	}
	free(path);
	return var;
}


} // namespace


std::map<std::string, DataHolder::Ptr> DataHolderFactory::createDeviceDataHolders(
	Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier)
{
	std::map<std::string, DataHolder::Ptr> map;
	if(controller->error().isNoError())
	{
		ZWay zway = ZWayController::convert(controller);
		ZDataHolder d = DataUtil::findDeviceData(zway, identifier, ".");
		zdata_acquire_lock(ZDataRoot(zway));
		ZDataIterator child = zdata_first_child(d);
		while (child != nullptr)
		{
			// devices.1.data.SDK -> SDK
			Poco::SharedPtr<ZWayDataHolder> dataPtr = new ZWayDataHolder(controller);
			std::string var = getPathVariable(child->data);
			ZDataHolder data = DataUtil::findDeviceData(zway, identifier, var);
			dataPtr->setData(data);
			map[var] = dataPtr;
			child = zdata_next_child(child);
		}
		zdata_release_lock(ZDataRoot(zway));
	}
	return map;
}

std::map<std::string, DataHolder::Ptr> DataHolderFactory::createInstanceDataHolders(
	Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance)
{
	std::map<std::string, DataHolder::Ptr> map;
	if(controller->error().isNoError())
	{
		ZWay zway = ZWayController::convert(controller);
		ZDataHolder d = DataUtil::findInstanceData(zway, identifier, instance, ".");
		zdata_acquire_lock(ZDataRoot(zway));
		ZDataIterator child = zdata_first_child(d);
		while (child != nullptr)
		{
			// devices.1.instances.0.data.dynamic -> dynamic
			Poco::SharedPtr<ZWayDataHolder> dataPtr = new ZWayDataHolder(controller);
			std::string var = getPathVariable(child->data);
			ZDataHolder data = DataUtil::findInstanceData(zway, identifier, instance, var);
			dataPtr->setData(data);
			map[var] = dataPtr;
			child = zdata_next_child(child);
		}
		zdata_release_lock(ZDataRoot(zway));
	}
	return map;
}

std::map<std::string, DataHolder::Ptr> DataHolderFactory::createCommandClassHolders(Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId)
{
	return searchAndCreateCommandClassHolders(controller, identifier, instance, classId, ".");
}

std::map<std::string, DataHolder::Ptr> DataHolderFactory::searchAndCreateCommandClassHolders(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId,
	const std::string& dataPath)
{
	std::map<std::string, DataHolder::Ptr> map;
	if(controller->error().isNoError())
	{
		ZWay zway = ZWayController::convert(controller);
		ZDataHolder d = DataUtil::findCommandClassData(zway, identifier, instance, classId, dataPath);
		zdata_acquire_lock(ZDataRoot(zway));
		ZDataIterator child = zdata_first_child(d);
		while (child != nullptr)
		{
			// devices.1.instances.1.commandClasses.32.data.level -> level
			std::string var = getPathVariable(child->data);
			map[var] = searchAndCreateCommandClassHolder(controller, identifier, instance, classId, var);
			child = zdata_next_child(child);
		}
		zdata_release_lock(ZDataRoot(zway));
	}
	return map;
}

DataHolder::Ptr DataHolderFactory::searchAndCreateCommandClassHolder(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId,
	const std::string& dataPath)
{
	Poco::SharedPtr<ZWayDataHolder> dataPtr = new ZWayDataHolder(controller);
	if(controller->error().isNoError())
	{
		ZWay zway = ZWayController::convert(controller);
		zdata_acquire_lock(ZDataRoot(zway));
		ZDataHolder data = DataUtil::findCommandClassData(zway, identifier, instance, classId, dataPath);
		dataPtr->setData(data);
		zdata_release_lock(ZDataRoot(zway));
	}
	return dataPtr;
}


} } } // namespace IoT::ZWave::Way
