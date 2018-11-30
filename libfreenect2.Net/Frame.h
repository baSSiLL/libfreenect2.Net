#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"
#include "FrameDataFormat.h"

namespace libfreenect2Net
{
	public ref class Frame : public Internals::ManagedWrapper<libfreenect2::Frame>
	{
	private:
		initonly TimeSpan _timeStamp;
		Frame(libfreenect2::Frame* instance);

	internal:
		static explicit operator Frame^ (libfreenect2::Frame* instance);

	public:
		property int Width
		{
			int get() { return (int)Instance->width; }
		}

		property int Height
		{
			int get() { return (int)Instance->height; }
		}

		property FrameDataFormat DataFormat
		{
			FrameDataFormat get() { return (FrameDataFormat)Instance->format; }
		}

		property int BytesPerPixel
		{
			int get() { return (int)Instance->bytes_per_pixel; }
		}

		property IntPtr Data
		{
			IntPtr get() { return IntPtr(Instance->data); }
		}

		property TimeSpan TimeStamp
		{
			TimeSpan get() { return _timeStamp; }
		}

		/// <summary>Sequence number of the frame.</summary>
		/// <remarks>Simple increasing counter.</summary>
		property long long Sequence
		{
			long long get() { return (long)Instance->sequence; }
		}

		/// <summary>Exposure value for the frame.</summary>
		/// <remarks>Ranges from 0.5 (bright light) to ~60.0 (sensor covered).
		property float Exposure
		{
			float get() { return Instance->exposure; }
		}

		/// <summary>Gain value for the frame.</summary>
		/// <remarks>Ranges from 1.0 (bright light) to 1.5 (sensor covered).
		property float Gain
		{
			float get() { return Instance->gain; }
		}

		/// <summary>Gamma value for the frame.</summary>
		/// <remarks>Ranges from 1.0 (bright light) to 6.4 (sensor covered).
		property float Gamma
		{
			float get() { return Instance->gamma; }
		}

		/// <summary>Indicates whether the frame has an error.</summary>
		/// <remarks>Possible errors are not specified, as well as which properties they affect.</remarks>
		property bool HasError
		{
			bool get() { return Instance->status != 0; }
		}
	};
}