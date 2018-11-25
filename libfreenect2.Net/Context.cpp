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

	Device^ Context::OpenDevice(int deviceIndex, PacketPipeline^ pipeline)
	{
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDevice(deviceIndex)
			: Instance->openDevice(deviceIndex, pipeline);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDevice(String^ serialNumber, PacketPipeline^ pipeline)
	{
		std::string sSerialNumber = marshal_as<std::string>(serialNumber);
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDevice(sSerialNumber)
			: Instance->openDevice(sSerialNumber, pipeline);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDefaultDevice(PacketPipeline^ pipeline)
	{
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDefaultDevice()
			: Instance->openDefaultDevice(pipeline);
		return static_cast<Device^>(result);
	}
}