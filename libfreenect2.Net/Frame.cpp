#include "Frame.h"
#include "Implementation.h"

using namespace System;

namespace libfreenect2Net
{
	Frame::Frame(libfreenect2::Frame* instance)
		: ManagedWrapper(instance)
	{
		// Convert time stamp from 0.125 ms units
		_timeStamp = TimeSpan::FromTicks(instance->timestamp * TimeSpan::TicksPerMillisecond / 8);
	}

	Frame::operator libfreenect2Net::Frame ^ (libfreenect2::Frame* instance)
	{
		return CAST_TO_MANAGED(Frame, instance);
	}
}