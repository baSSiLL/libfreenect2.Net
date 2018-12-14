#include "Device.h"
#include "Implementation.h"

namespace libfreenect2Net
{
	Device::Device(libfreenect2::Freenect2Device* instance)
		: ManagedWrapper(instance)
	{
		System::Collections::Concurrent::ConcurrentDictionary<IntPtr, Device^>^ dict = gcnew System::Collections::Concurrent::ConcurrentDictionary<IntPtr, Device^>();
	}

	Device::operator Device^ (libfreenect2::Freenect2Device* instance)
	{
		if (instance == nullptr)
			return nullptr;

		IntPtr key = IntPtr(instance);
		// Create a new instance beforehand (little overhead)
		Device^ newWrapper = gcnew Device(instance);
		Device^ result = _instanceWrapperMap->GetOrAdd(key, newWrapper);
		if (!ReferenceEquals(result, newWrapper))
		{
			// There is existing instance already => throw away the new one
			newWrapper->Detach();
		}
		return result;
	}

	Device::~Device()
	{
		if (!this->IsDisposed)
		{
			IntPtr key = IntPtr(Instance);
			Device^ value = this;
			Device^% valueRef = value;
			_instanceWrapperMap->TryRemove(key, valueRef);
		}
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

	ColorCameraParameters Device::ColorCameraParameters::get()
	{
		libfreenect2::Freenect2Device::ColorCameraParams params = Instance->getColorCameraParams();
		// Implicit conversion operator
		return params;
	}

	InfraRedCameraParameters Device::InfraRedCameraParameters::get()
	{
		libfreenect2::Freenect2Device::IrCameraParams params = Instance->getIrCameraParams();
		// Implicit conversion operator
		return params;
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

	bool Device::StartAll()
	{
		return Instance->start();
	}

	bool Device::StartColor()
	{
		return Instance->startStreams(true, false);
	}

	bool Device::StartDepth()
	{
		return Instance->startStreams(false, true);
	}

	bool Device::Stop()
	{
		return Instance->stop();
	}

	bool Device::Close()
	{
		return Instance->close();
	}
}