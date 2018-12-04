#include <msclr\marshal_cppstd.h>
#include "Context.h"

using namespace libfreenect2;
using namespace msclr::interop;

namespace libfreenect2Net
{
	Context::Context()
		: ManagedWrapper(new libfreenect2::Freenect2())
	{
	}

	int Context::EnumerateDevices()
	{
		return Instance->enumerateDevices();
	}

	String^ Context::GetDeviceSerialNumber(int deviceIndex)
	{
		std::string result = Instance->getDeviceSerialNumber(deviceIndex);
		return gcnew String(result.c_str());
	}

	String^ Context::GetDefaultDeviceSerialNumber()
	{
		std::string result = Instance->getDefaultDeviceSerialNumber();
		return gcnew String(result.c_str());
	}

	Device^ Context::OpenDevice(int deviceIndex)
	{
		Freenect2Device* result = Instance->openDevice(deviceIndex);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDevice(String^ serialNumber)
	{
		std::string sSerialNumber = marshal_as<std::string>(serialNumber);
		Freenect2Device* result = Instance->openDevice(sSerialNumber);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDefaultDevice()
	{
		Freenect2Device* result = Instance->openDefaultDevice();
		return static_cast<Device^>(result);
	}
}