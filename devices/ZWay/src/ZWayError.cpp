#include "ZWayError.h"

#include <utility>

namespace IoT {
namespace ZWave {
namespace Way {


ZWayError::ZWayError(std::string errorMessage) : errorMessage_(std::move(errorMessage))
{
}

ZWayError::ZWayError(std::string errorMessage, ZWError zWError)
	: zWError_(zWError), errorMessage_(std::move(errorMessage))
{
}

Error ZWayError::error() const
{
	std::string msg = errorMessage_ + ". Error message: ";
	msg.append(" Error: ");
	switch (zWError_)
	{
	case 0:
		msg += "No error.";
		break;
	case -1:
		msg += "Bad arguments.";
		break;
	case -2:
		msg += "Malloc errors.";
		break;
	case -3:
		msg += "Not implemented by the library.";
		break;
	case -4:
		msg += "Function class not supported by the hardware.";
		break;
	case -5:
		msg += "Access denied."; // -- not used
		break;
	case -6:
		msg += "Threading error.";
		break;
	case -7:
		msg += "Invalid operation"; // -- not used
		break;
	case -8:
		msg += "Internal consistency error.";
		break;
	case -9:
		msg += "Wrong packet from Z-Wave network or Discovery got bad data "
				 "(stick communication failed).";
		break;
	case -10:
		msg += "Wrong data type requested.";
		break;
	case -12:
		msg += "Object accessed from invalid thread.";
		break;
	case -20:
		msg += "Can not open port.";
		break;
	case -21:
		msg += "Error reading configuration and translation files.";
		break;

	// other errors
	case -25:
		msg += "Controller is not primary.";
		break;


	// internal codes - never exposed to outside
	case -30:
		msg += "Can not remove job from queue: job not found.";
		break;
	case -31:
		msg += "Job is already in the queue.";
		break;
	case -32:
		msg += "Queueing of duplicate job. New job removed, callbacks merged "
				 "with old one.";
		break;
	case -40:
		msg += "Packet is too big to be encapsulated in MultiCmd - sending "
				 "non-encapsulated.";
		break;

	default:
		msg += "Error";
	}

	return Error(msg, zWError_);
}


} } } // namespace IoT::ZWave::Device
