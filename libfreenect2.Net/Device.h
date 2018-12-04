#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include <list>
#include "ManagedWrapper.h"
#include "FrameListener.h"

using namespace System;
using namespace System::Collections::Concurrent;

namespace libfreenect2Net
{
	public ref class Device : public Internals::ManagedWrapper<libfreenect2::Freenect2Device>
	{
	private:
		static initonly ConcurrentDictionary<IntPtr, Device^>^ _instanceWrapperMap = gcnew ConcurrentDictionary<IntPtr, Device^>();

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

		bool StartAll();
		bool StartColor();
		bool StartDepth();
		bool Stop();
		bool Close();
	};
}