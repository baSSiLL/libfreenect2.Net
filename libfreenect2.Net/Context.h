#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"

using namespace System;

namespace libfreenect2Net
{
	public ref class Context : public Internals::ManagedWrapper<libfreenect2::Freenect2>
	{
	public:
		Context();
		int EnumerateDevices();
		String^ GetDeviceSerialNumber(int deviceIndex);
		String^ GetDefaultDeviceSerialNumber();
	};
}
