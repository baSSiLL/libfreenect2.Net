#include "Frame.h"
#include "Implementation.h"

using namespace System;
using namespace libfreenect2Net::Internals;

namespace libfreenect2Net
{
	Frame::Frame(libfreenect2::Frame* instance)
		: ManagedWrapper(instance)
	{
		// Convert time stamp from 0.125 ms units
		_timeStamp = TimeSpan::FromTicks(instance->timestamp * TimeSpan::TicksPerMillisecond / 8);
	}

	Frame::Frame(int width, int height, FrameDataFormat dataFormat)
		: ManagedWrapper(new libfreenect2::Frame(Checks::IsPositive(width, "width"), 
												 Checks::IsPositive(height, "height"), 
												 GetBytesPerPixelForDataFormat(dataFormat)))
	{
		Instance->format = ConvertDataFormat(dataFormat);
	}

	Frame::operator libfreenect2Net::Frame ^ (libfreenect2::Frame* instance)
	{
		return CAST_TO_MANAGED(Frame, instance);
	}

	int Frame::DataSize::get()
	{
		switch (DataFormat)
		{
		case FrameDataFormat::Raw:
			return BytesPerPixel;
		case FrameDataFormat::Bgrx:
		case FrameDataFormat::Rgbx:
		case FrameDataFormat::Float:
		case FrameDataFormat::Gray:
			return BytesPerPixel * Width * Height;
		default:
			return -1;
		}
	}

	int Frame::GetBytesPerPixelForDataFormat(FrameDataFormat dataFormat)
	{
		switch (dataFormat)
		{
		case FrameDataFormat::Bgrx:
		case FrameDataFormat::Rgbx:
		case FrameDataFormat::Float:
			return 4;
		case FrameDataFormat::Gray:
			return 1;
		default:
			throw gcnew ArgumentOutOfRangeException("dataFormat");
		}
	}

	libfreenect2::Frame::Format Frame::ConvertDataFormat(FrameDataFormat value)
	{
		switch (value)
		{
		case FrameDataFormat::Bgrx: return libfreenect2::Frame::Format::BGRX;
		case FrameDataFormat::Rgbx: return libfreenect2::Frame::Format::RGBX;
		case FrameDataFormat::Float: return libfreenect2::Frame::Format::Float;
		case FrameDataFormat::Gray: return libfreenect2::Frame::Format::Gray;
		case FrameDataFormat::Raw: return libfreenect2::Frame::Format::Raw;
		case FrameDataFormat::Invalid: return libfreenect2::Frame::Format::Invalid;
		default:
			throw gcnew ArgumentOutOfRangeException("value");
		}
	}
}