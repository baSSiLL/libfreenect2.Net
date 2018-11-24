#include "Context.h"

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
}