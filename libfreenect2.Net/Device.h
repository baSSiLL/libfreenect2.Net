#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include <list>
#include "ManagedWrapper.h"
#include "FrameListener.h"

using namespace System;

namespace libfreenect2Net
{
	public ref class Device : public Internals::ManagedWrapper<libfreenect2::Freenect2Device>
	{
	private:
		FrameListenerAdapter* _colorListener;
		FrameListenerAdapter* _depthListener;

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

		void SetColorListener(IFrameListener^ listener);
		void SetDepthListener(IFrameListener^ listener);

		void StartAll();
		void StartColor();
		void StartDepth();
		void Stop();
		void Close();
	};
}