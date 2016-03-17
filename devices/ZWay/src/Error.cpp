#include "IoT/ZWave/Way/Error.h"

#include <utility>

namespace IoT {
namespace ZWave {
namespace Way {


Error::Error(std::string errorMessage, int state)
	: state_(state), errorMessage_(std::move(errorMessage))
{
}

bool Error::isError() const { return state_ != 0; }

bool Error::isNoError() const { return state_ == 0; }

std::string Error::errorMessage() const
{
	return errorMessage_;
}


} } } // namespace IoT::ZWave::Device
