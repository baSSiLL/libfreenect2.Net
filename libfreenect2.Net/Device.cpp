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
		libfreenect2Net::ColorCameraParameters result;

		result.FocalLengthX = params.fx;
		result.FocalLengthY = params.fy;
		result.PrincipalPointX = params.cx;
		result.PrincipalPointY = params.cy;

		result.Extrinsics.shift_d = params.shift_d;
		result.Extrinsics.shift_m = params.shift_m;

		result.Extrinsics.mx_x3y0 = params.mx_x3y0;
		result.Extrinsics.mx_x0y3 = params.mx_x0y3;
		result.Extrinsics.mx_x2y1 = params.mx_x2y1;
		result.Extrinsics.mx_x1y2 = params.mx_x1y2;
		result.Extrinsics.mx_x2y0 = params.mx_x2y0;
		result.Extrinsics.mx_x0y2 = params.mx_x0y2;
		result.Extrinsics.mx_x1y1 = params.mx_x1y1;
		result.Extrinsics.mx_x1y0 = params.mx_x1y0;
		result.Extrinsics.mx_x0y1 = params.mx_x0y1;
		result.Extrinsics.mx_x0y0 = params.mx_x0y0;

		result.Extrinsics.my_x3y0 = params.my_x3y0;
		result.Extrinsics.my_x0y3 = params.my_x0y3;
		result.Extrinsics.my_x2y1 = params.my_x2y1;
		result.Extrinsics.my_x1y2 = params.my_x1y2;
		result.Extrinsics.my_x2y0 = params.my_x2y0;
		result.Extrinsics.my_x0y2 = params.my_x0y2;
		result.Extrinsics.my_x1y1 = params.my_x1y1;
		result.Extrinsics.my_x1y0 = params.my_x1y0;
		result.Extrinsics.my_x0y1 = params.my_x0y1;
		result.Extrinsics.my_x0y0 = params.my_x0y0;

		return result;
	}

	InfraRedCameraParameters Device::InfraRedCameraParameters::get()
	{
		libfreenect2::Freenect2Device::IrCameraParams params = Instance->getIrCameraParams();
		libfreenect2Net::InfraRedCameraParameters result;

		result.FocalLengthX = params.fx;
		result.FocalLengthY = params.fy;
		result.PrincipalPointX = params.cx;
		result.PrincipalPointY = params.cy;

		result.Distortion.K1 = params.k1;
		result.Distortion.K2 = params.k2;
		result.Distortion.K3 = params.k3;

		result.Distortion.P1 = params.p1;
		result.Distortion.P2 = params.p2;

		return result;
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