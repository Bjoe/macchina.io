#include "IoT/ZWave/NodesManager.h"

#include <string>

#include "Poco/OSP/Properties.h"
#include "Poco/OSP/ServiceRegistry.h"

#include "Poco/NumericString.h"

#include "CommandClassFactory.h"
#include "IoT/ZWave/BaseCommandClass.h"


namespace IoT {
namespace ZWave {


NodesManager::NodesManager(Way::Controller::Ptr controller,
	Poco::OSP::BundleContext::Ptr bundleContext,
	Poco::Logger& log)
	: controller_(controller), bundleContext_(bundleContext), log_(log)
{
}

void NodesManager::deviceAdded(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();
	Node* node = new Node(controller_, id);
	nodes_[id] = node;
	log_.information("Added device %#x", id);

	registerNode(id);
}

void NodesManager::deviceRemoved(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();

	auto iter =	serviceRefs_.find(id);
	Poco::OSP::ServiceRef::Ptr serviceRef = iter->second;
	bundleContext_->registry().unregisterService(serviceRef);

	auto nodeIter = nodes_.find(id);
	Node* node = nodeIter->second;
	delete node;
	nodes_.erase(nodeIter);

	log_.information("Removed device %#x", id);
}

void NodesManager::instanceAdded(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();
	if (isDeviceExists(id))
	{
		deviceAdded(event);
	}

	Way::NodeInstance instanceId = event.instanceId();
	nodes_[id]->addInstance(instanceId);
	log_.information("Added instance %u for device %#x", instanceId, id);
}

void NodesManager::instanceRemoved(Way::Event event)
{
	Way::NodeInstance instanceId = event.instanceId();
	Way::NodeIdentifier id = event.nodeId();
	nodes_[id]->removeInstance(instanceId);
	log_.information("Removed instance %u", instanceId, id);
}

void NodesManager::commandAdded(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();
	if (isDeviceExists(id))
	{
		deviceAdded(event);
	}

	Way::NodeInstance instanceId = event.instanceId();
	Way::CommandClassId classId = event.commandClass();
	BaseCommandClass::Ptr commandClass =
		CommandClassFactory::create(controller_, id, instanceId, classId);
	std::string commandName = commandClass->commandClassName();

	if (instanceId != 0u)
	{
		nodes_[id]->addCommandClass(instanceId, commandClass);
		log_.information(
			"Added command class %#x name %s for instance %u and device %#x",
			classId,
			commandName,
			instanceId,
			id);
	}
	else
	{
		nodes_[id]->addCommandClass(commandClass);
		log_.information(
			"Added command class %#x name %s for device %#x",
			classId,
			commandName,
			id);
	}
}

void NodesManager::commandRemoved(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();
	Way::NodeInstance instanceId = event.instanceId();
	Way::CommandClassId classId = event.commandClass();
	if (instanceId != 0u)
	{
		nodes_[id]->removeCommandClass(instanceId, classId);
		log_.information(
			"Removed command %#x for instance %u and device %#x",
			classId,
			instanceId,
			id);
	}
	else
	{
		nodes_[id]->removeCommandClass(classId);
		log_.information("Removed command %#x for device %#x", classId, id);
	}
}

void NodesManager::unknown(Way::Event event)
{
	Way::NodeIdentifier id = event.nodeId();
	Way::NodeInstance instanceId = event.instanceId();
	Way::CommandClassId classId = event.commandClass();

	log_.error(
		"Unhandle event: Device %#x instance %u command %#x",
		id,
		instanceId,
		classId);
}

void NodesManager::removeAllNodes()
{
	for (auto& service : serviceRefs_)
	{
		Way::NodeIdentifier nodeId = service.first;
		Poco::OSP::ServiceRef::Ptr serviceRef = service.second;
		bundleContext_->registry().unregisterService(serviceRef);
		auto serviceIter = serviceRefs_.find(nodeId);
		serviceRefs_.erase(serviceIter);
		auto nodeIter = nodes_.find(nodeId);
		nodes_.erase(nodeIter);
	}

	for (auto& nodePair : nodes_)
	{
		Node* node = nodePair.second;
		delete node;
		Way::NodeIdentifier nodeId = nodePair.first;
		auto nodeIter = nodes_.find(nodeId);
		nodes_.erase(nodeIter);
	}
}

void NodesManager::triggerTask(Poco::Timer&)
{
	for (auto& nodeIter : nodes_)
	{
		Node* node = nodeIter.second;
		Way::NodeIdentifier id = node->id();
		if (id != 1 && !node->isInterviewDone())
		{
			//log_.information("Interview for node %#x is not done yet", id);
			// node->forceReInterview();
			std::map<Way::CommandClassId, BaseCommandClass::Ptr> commands = node->getCommandClasses();
			for (auto& commandPair : commands)
			{
				BaseCommandClass::Ptr command = commandPair.second;
				Way::CommandClassId classId = command->commandClassId();
				if (!command->isInterviewDone())
				{
					log_.information(
						"Interview for node %#x and command %#x is not done yet",
						id,
						classId);
					Way::Error error = command->runInterview();
					if (error.isError())
					{
						log_.error(
							"Interview error for node %#x command %#x Error: %s",
							id,
							classId,
							error.errorMessage());
					}
				}
			}
			std::vector<Way::NodeInstance> instanceIds = node->getInstances();
			if (!instanceIds.empty())
			{
				for (auto& instanceId : instanceIds)
				{
					std::map<Way::CommandClassId, BaseCommandClass::Ptr> commands = node->getCommandClassesForInstance(instanceId);
					for (auto& commandPair : commands)
					{
						BaseCommandClass::Ptr command = commandPair.second;
						Way::CommandClassId classId = command->commandClassId();
						if (!command->isInterviewDone())
						{
							log_.information(
								"Interview for node %#x instance %#x command %#x is not done yet",
								id,
								instanceId,
								classId);
							Way::Error error = command->runInterview();
							if (error.isError())
							{
								log_.error(
									"Interview error for node %#x instance %#x command %#x Error: %s",
									id,
									instanceId,
									classId,
									error.errorMessage());
							}
						}
					}
				}
			}
		}
	}
}

void NodesManager::registerNode(Way::NodeIdentifier id)
{
	std::string idStr;
	Poco::uIntToStr(id, 10, idStr);
	std::string oid(Node::SYMBOLIC_NAME);
	oid += '#';
	oid += idStr;

	Poco::OSP::Properties props;
	props.set("NodeId", idStr);

	Node* node = nodes_[id];
	Poco::OSP::ServiceRef::Ptr serviceRef =	bundleContext_->registry().registerService(oid, node, props);
	serviceRefs_[id] = serviceRef;
	log_.information("Node add as service %#x %s", id, oid);
}

bool NodesManager::isDeviceExists(Way::NodeIdentifier id)
{
	auto iter = nodes_.find(id);
	return iter == nodes_.end();
}


} } // namespace IoT::ZWave
