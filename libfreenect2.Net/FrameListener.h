#pragma once

#include <vcclr.h>
#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"
#include "FrameType.h"
#include "Frame.h"

namespace libfreenect2Net
{
	public interface class IFrameListener
	{
	public:
		bool OnNewFrame(FrameType frameType, Frame^ frame);
	};


	private class FrameListenerAdapter : public libfreenect2::FrameListener
	{
	private:
		gcroot<IFrameListener^> _impl;

	public:
		FrameListenerAdapter(IFrameListener^ impl);
		bool onNewFrame(libfreenect2::Frame::Type type, libfreenect2::Frame* frame);
	};
}

