#include "ShowNodes.h"

#include <vector>

#include "Poco/Dynamic/Var.h"
#include "Poco/Format.h"
#include "Poco/JSON/Array.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceRegistry.h"

#include "IoT/ZWave/Node.h"
#include "IoT/ZWave/Way/DataHolder.h"
#include "IoT/ZWave/Way/Defs.h"


namespace IoT {
namespace Web {
namespace ZWave {
namespace Command {


ShowNodes::ShowNodes() {}

Poco::JSON::Object ShowNodes::handle(
	Poco::OSP::BundleContext::Ptr bundleContext,
	Poco::SharedPtr<Poco::Net::HTMLForm> /*form*/) const
{
	Poco::JSON::Object nodesResult(true);

	std::vector<Poco::OSP::ServiceRef::Ptr> services;
	bundleContext->registry().find(R"(name =~ ")" + std::string(IoT::ZWave::Node::SYMBOLIC_NAME) + R"(#*")", services);

	Poco::JSON::Array::Ptr list = new Poco::JSON::Array();
	for (auto& service : services)
	{
		Poco::JSON::Object::Ptr nodeResult = new Poco::JSON::Object(true);
		IoT::ZWave::Node::Ptr node = service->castedInstance<IoT::ZWave::Node>();
		IoT::ZWave::Way::NodeIdentifier nodeIdentifier = node->id();
		nodeResult->set("node_identifier", nodeIdentifier);

		Poco::JSON::Object::Ptr dataHoldersResult = new Poco::JSON::Object(true);
		std::map<std::string, IoT::ZWave::Way::DataHolder::Ptr> dataHolders = node->getDataHolders();
		for (auto& dataHolderPair : dataHolders)
		{
			std::string name = dataHolderPair.first;
			IoT::ZWave::Way::DataHolder::Ptr dataHolder = dataHolderPair.second;
			Poco::Dynamic::Var::Ptr value = dataHolder->getValue();
			std::string val("Empty");
			if (!value->isEmpty())
			{
				val = value->toString();
			}
			dataHoldersResult->set(name, val);
		}		
		nodeResult->set("data_holders", dataHoldersResult);
		list->add(nodeResult);
	}
	nodesResult.set("nodes", list);
	return nodesResult;
}


} } } } // namespace IoT::Web::ZWave::Command
