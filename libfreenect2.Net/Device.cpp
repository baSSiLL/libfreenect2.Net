#include "Device.h"

namespace libfreenect2Net
{
	Device::Device(libfreenect2::Freenect2Device* instance)
		: ManagedWrapper(instance)
	{
	}

	Device::~Device()
	{
		Instance->close();
	}

	Device::operator Device^ (libfreenect2::Freenect2Device* instance)
	{
		return instance == nullptr ? nullptr : gcnew Device(instance);
	}

	String^ Device::SerialNumber::get()
	{
		std::string result = Instance->getSerialNumber();
		return gcnew String(result.c_str());
	}

	String^ Device::FirmwareVersion::get()
	{
		std::string result = Instance->getFirmwareVersion();
		return gcnew String(result.c_str());
	}

	void Device::StartAll()
	{
		Instance->start();
	}

	void Device::StartRgb()
	{
		Instance->startStreams(true, false);
	}

	void Device::StartDepth()
	{
		Instance->startStreams(false, true);
	}

	void Device::Stop()
	{
		Instance->stop();
	}

	void Device::Close()
	{
		Instance->close();
	}
}