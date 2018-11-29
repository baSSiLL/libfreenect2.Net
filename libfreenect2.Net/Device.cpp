#include "Device.h"
#include "Implementation.h"

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
		return CAST_TO_MANAGED(Device, instance);
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

	void Device::SetColorListener(IFrameListener^ listener)
	{
		FrameListenerAdapter* adapter = listener == nullptr ? nullptr : new FrameListenerAdapter(listener);
		Instance->setColorFrameListener(adapter);
		
		if (_colorListener != nullptr)
		{
			delete _colorListener;
		}
		_colorListener = adapter;
	}

	void Device::SetDepthListener(IFrameListener^ listener)
	{
		FrameListenerAdapter* adapter = listener == nullptr ? nullptr : new FrameListenerAdapter(listener);
		Instance->setIrAndDepthFrameListener(adapter);

		if (_depthListener != nullptr)
		{
			delete _depthListener;
		}
		_depthListener = adapter;
	}

	void Device::StartAll()
	{
		Instance->start();
	}

	void Device::StartColor()
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