#include "FrameListener.h"
#include "Implementation.h"

namespace libfreenect2Net
{
	FrameListenerAdapter::FrameListenerAdapter(IFrameListener^ impl)
	{
		this->_impl = impl;
	}

	bool FrameListenerAdapter::onNewFrame(libfreenect2::Frame::Type type, libfreenect2::Frame* frame)
	{
		return _impl->OnNewFrame((FrameType)type, static_cast<Frame^>(frame));
	}
}
