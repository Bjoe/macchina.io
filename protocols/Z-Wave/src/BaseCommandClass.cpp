#include "IoT/ZWave/BaseCommandClass.h"

#include "IoT/ZWave/Way/DataHolderFactory.h"


namespace IoT {
namespace ZWave {


BaseCommandClass::BaseCommandClass(Way::Controller::Ptr controller,
	Way::NodeIdentifier identifier,
	Way::NodeInstance instance,
	Way::CommandClassId classId)
	: controller_(controller),
	  identifier_(identifier),
	  instance_(instance),
	  classId_(classId),
	  dataHolders_(Way::DataHolderFactory::createCommandClassHolders(
					   controller_, identifier, instance, classId))
{
}

Way::Error BaseCommandClass::reportValue() const { return Way::Error(); }

Poco::Dynamic::Var::Ptr BaseCommandClass::getValue() const
{
	return new Poco::Dynamic::Var();
}

Way::DataHolder::Ptr BaseCommandClass::getDataHolder() const
{
	Way::DataHolder::Ptr holder;
	return holder;
}

Way::Error BaseCommandClass::setValue(const Poco::Dynamic::Var& /*unused*/)
{
	return Way::Error();
}

bool BaseCommandClass::isInterviewDone() const
{
	Poco::Dynamic::Var::Ptr value = getDataHolderValue("interviewDone");
	bool result = value->convert<bool>();
	return result;
}

Way::Error BaseCommandClass::runInterview() const
{
	return controller_->runCommandClassInterview(identifier_, instance_, classId_);
}

Poco::Dynamic::Var::Ptr BaseCommandClass::getDataHolderValue(const std::string& dataHolderName) const
{
	Poco::Dynamic::Var::Ptr value = new Poco::Dynamic::Var();
	Way::DataHolder::Ptr holder = getDataHolder(dataHolderName);
	if (!holder.isNull())
	{
		value = holder->getValue();
	}
	return value;
}

Way::DataHolder::Ptr BaseCommandClass::getDataHolder(const std::string& dataHolderName) const
{
	Way::DataHolder::Ptr holder;
	auto itr = dataHolders_.find(dataHolderName);
	if (itr != dataHolders_.end())
	{
		holder = itr->second;
	}
	return holder;
}


} } // namespace IoT::ZWave
