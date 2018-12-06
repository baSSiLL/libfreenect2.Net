#include <msclr\marshal_cppstd.h>
#include "Context.h"
#include "StreamProcessors.h"

using namespace libfreenect2;
using namespace msclr::interop;

// Defined in PacketPipelineFactory.cpp
PacketPipeline* GetPacketPipeline(libfreenect2Net::ColorProcessor colorProcessor, libfreenect2Net::DepthProcessor depthProcessor);

namespace libfreenect2Net
{
	Context::Context()
		: ManagedWrapper(new Freenect2())
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

	Device^ Context::OpenDevice(int deviceIndex, ColorProcessor colorProcessor, DepthProcessor depthProcessor)
	{
		PacketPipeline* pipeline = GetPacketPipeline(colorProcessor, depthProcessor);
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDevice(deviceIndex)
			: Instance->openDevice(deviceIndex, pipeline);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDevice(String^ serialNumber, ColorProcessor colorProcessor, DepthProcessor depthProcessor)
	{
		PacketPipeline* pipeline = GetPacketPipeline(colorProcessor, depthProcessor);
		std::string sSerialNumber = marshal_as<std::string>(serialNumber);
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDevice(sSerialNumber)
			: Instance->openDevice(sSerialNumber, pipeline);
		return static_cast<Device^>(result);
	}

	Device^ Context::OpenDefaultDevice(ColorProcessor colorProcessor, DepthProcessor depthProcessor)
	{
		PacketPipeline* pipeline = GetPacketPipeline(colorProcessor, depthProcessor);
		Freenect2Device* result = pipeline == nullptr
			? Instance->openDefaultDevice()
			: Instance->openDefaultDevice(pipeline);
		return static_cast<Device^>(result);
	}
}