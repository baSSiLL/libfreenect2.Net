#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"

using namespace System;

namespace libfreenect2Net
{
	public ref class Device : public Internals::ManagedWrapper<libfreenect2::Freenect2Device>
	{
	private:
		Device(libfreenect2::Freenect2Device* instance);

	internal:
		static explicit operator Device^ (libfreenect2::Freenect2Device* instance);

	public:
		virtual ~Device();

		property String^ SerialNumber
		{ 
			String^ get(); 
		};

		property String^ FirmwareVersion
		{
			String^ get();
		}

		void StartAll();
		void StartRgb();
		void StartDepth();
		void Stop();
		void Close();
	};
}