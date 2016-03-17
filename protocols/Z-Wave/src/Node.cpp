#include "IoT/ZWave/Node.h"

#include <utility>

#include "IoT/ZWave/Way/DataHolderFactory.h"


namespace IoT {
namespace ZWave {


Node::Node(Way::Controller::Ptr controller, Way::NodeIdentifier nodeId)
	: zWay_(controller), nodeId_(nodeId)
{
}

const std::type_info& Node::type() const { return typeid(Node); }

bool Node::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name() || Node::isA(otherType);
}

Way::NodeIdentifier Node::id() const { return nodeId_; }

bool Node::isInterviewDone() const { return zWay_->isInterviewiDone(nodeId_); }

Way::Error Node::forceReInterview() const
{
	return zWay_->forceDeviceInterview(nodeId_);
}

Way::Error Node::sendNop() const { return zWay_->sendDeviceNop(nodeId_); }

Way::Error Node::loadXml(const std::string& fileName)
{
	return zWay_->loadXmlForDevice(nodeId_, fileName);
}

std::vector<Way::NodeInstance> Node::getInstances() const
{
	std::vector<Way::NodeInstance> instances;
	for (auto& iter : instances_)
	{
		instances.push_back(iter.first);
	}
	return instances;
}

std::map<std::string, Way::DataHolder::Ptr> Node::getDataHolders() const
{
	return Way::DataHolderFactory::createDeviceDataHolders(zWay_, nodeId_);
}

std::map<std::string, Way::DataHolder::Ptr> Node::getDataHoldersForInstance(
	Way::NodeInstance instance) const
{
	return Way::DataHolderFactory::createInstanceDataHolders(
		zWay_, nodeId_, instance);
}

std::map<Way::CommandClassId, BaseCommandClass::Ptr>
Node::getCommandClasses() const
{
	return commandClassList_;
}

std::map<Way::CommandClassId, BaseCommandClass::Ptr>
Node::getCommandClassesForInstance(Way::NodeInstance instance) const
{
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> commandClasses;
	auto itr = instances_.find(instance);
	if (itr != instances_.end())
	{
		commandClasses = itr->second;
	}
	return commandClasses;
}

void Node::addInstance(Way::NodeInstance instance)
{
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> list;
	instances_[instance] = list;
}

void Node::removeInstance(Way::NodeInstance instance)
{
	auto it = instances_.find(instance);
	instances_.erase(it);
}

void Node::addCommandClass(BaseCommandClass::Ptr command)
{
	Way::CommandClassId classId = command->commandClassId();
	commandClassList_[classId] = command;
}

void Node::addCommandClass(
	Way::NodeInstance instance, BaseCommandClass::Ptr command)
{
	Way::CommandClassId classId = command->commandClassId();
	instances_[instance][classId] = command;
}

void Node::removeCommandClass(Way::CommandClassId commandId)
{
	auto it = commandClassList_.find(commandId);
	commandClassList_.erase(it);
}

void Node::removeCommandClass(
	Way::NodeInstance instance,
	Way::CommandClassId commandId)
{
	auto i = instances_.find(instance);
	std::map<Way::CommandClassId, BaseCommandClass::Ptr> commandList = (*i).second;
	auto it = commandList.find(commandId);
	commandList.erase(it);
}


} } // namespace IoT::ZWave
