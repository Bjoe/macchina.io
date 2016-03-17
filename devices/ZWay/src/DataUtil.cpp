#include "DataUtil.h"

#include "ZDataExt.h"
#include <cstdint>
#include <vector>

namespace IoT {
namespace ZWave {
namespace Way {


ZDataHolder DataUtil::findDeviceData(ZWay zway, NodeIdentifier identifier, const std::string& path)
{
	ZWBYTE id = identifier;
	zdata_acquire_lock(ZDataRoot(zway));
	ZDataHolder data = zway_find_device_data(zway, id, path.c_str());
	zdata_release_lock(ZDataRoot(zway));
	return data;
}

ZDataHolder DataUtil::findInstanceData(
		ZWay zway,
		NodeIdentifier identifier,
		NodeInstance instance,
		const std::string& path)
{
	zdata_acquire_lock(ZDataRoot(zway));
	ZDataHolder data = zway_find_device_instance_data(
			zway, identifier, instance, path.c_str());
	zdata_release_lock(ZDataRoot(zway));
	return data;
}

ZDataHolder DataUtil::findCommandClassData(
	ZWay zway,
	NodeIdentifier identifier,
	NodeInstance instance,
	CommandClassId classId,
	const std::string& path)
{
	zdata_acquire_lock(ZDataRoot(zway));
	ZDataHolder data = zway_find_device_instance_cc_data(
			zway, identifier, instance, classId, path.c_str());
	zdata_release_lock(ZDataRoot(zway));
	return data;
}

Poco::Dynamic::Var::Ptr DataUtil::getDataValue(ZDataHolder data)
{
	ZWDataType type;
	zdata_get_type(data, &type);

	Poco::Dynamic::Var::Ptr var = new Poco::Dynamic::Var();

	switch (type)
	{
	case Empty:
	{
		break;
	}
	case Boolean:
	{
		ZWBOOL boolValue;
		ZWError e = zdata_get_boolean(data, &boolValue);
		if (e == NoError)
		{
			bool value = false;
			if (boolValue != 0u)
			{
				value = true;
			}
			var = new Poco::Dynamic::Var(value);
		}
		break;
	}
	case Integer:
	{
		int intValue;
		ZWError e = zdata_get_integer(data, &intValue);
		if (e == NoError)
		{
			var = new Poco::Dynamic::Var(intValue);
		}
		break;
	}
	case Float:
	{
		float floatValue;
		ZWError e = zdata_get_float(data, &floatValue);
		if (e == NoError)
		{
			var = new Poco::Dynamic::Var(floatValue);
		}
		break;
	}
	case String:
	{
		ZWCSTR strValue;
		ZWError e = zdata_get_string(data, &strValue);
		if (e == NoError)
		{
			std::string str(strValue);
			var = new Poco::Dynamic::Var(str);
		}
		break;
	}
	case Binary:
	{
		size_t len;
		const ZWBYTE* binary;
		ZWError e = zdata_get_binary(data, &binary, &len);
		if (e == NoError)
		{
			std::vector<std::uint8_t> bytes(len);
			for (int i = 0; i < len; i++)
			{
				bytes[i] = binary[i];
			}
			var = new Poco::Dynamic::Var(bytes);
		}
		break;
	}
	case ArrayOfInteger:
	{
		size_t len;
		const int* intArray;
		ZWError e = zdata_get_integer_array(data, &intArray, &len);
		if (e == NoError)
		{
			std::vector<int> integer;
			for (int i = 0; i < len; i++)
			{
				integer[i] = intArray[i];
			}
			var = new Poco::Dynamic::Var(integer);
		}
		break;
	}
	case ArrayOfFloat:
	{
		size_t len;
		const float* floatArray;
		ZWError e = zdata_get_float_array(data, &floatArray, &len);
		if (e == NoError)
		{
			std::vector<float> floats;
			for (int i = 0; i < len; i++)
			{
				floats[i] = floatArray[i];
			}
			var = new Poco::Dynamic::Var(floats);
		}
		break;
	}
	case ArrayOfString:
	{
		size_t len;
		const ZWCSTR* strArray;
		ZWError e = zdata_get_string_array(data, &strArray, &len);
		if (e == NoError)
		{
			std::vector<std::string> strings;
			for (int i = 0; i < len; i++)
			{
				strings[i] = strArray[i];
			}
			var = new Poco::Dynamic::Var(strings);
		}
		break;
	}
	}
	return var;
}


} } } // namespace IoT::ZWave::Way
