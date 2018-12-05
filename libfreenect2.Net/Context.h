#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"
#include "Device.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace libfreenect2Net
{
	public ref class Context : public Internals::ManagedWrapper<libfreenect2::Freenect2>
	{
	public:
		static initonly int ColorFrameWidth = 1920;
		static initonly int ColorFrameHeight = 1080;
		static initonly int DepthFrameWidth = 512;
		static initonly int DepthFrameHeight = 424;

	public:
		Context();
		int EnumerateDevices();
		String^ GetDeviceSerialNumber(int deviceIndex);
		String^ GetDefaultDeviceSerialNumber();
		Device^ OpenDevice(int deviceIndex);
		Device^ OpenDevice(String^ serialNumber);
		Device^ OpenDefaultDevice();
	};
}
