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
		Frame^ f = static_cast<Frame^>(frame);
		bool calleeTookOwnershipOfFrame = _impl->OnNewFrame((FrameType)type, f);
		if (!calleeTookOwnershipOfFrame)
		{
			// let libfreenect manage the frame's lifetime
			f->Detach();
		}
		return calleeTookOwnershipOfFrame;
	}
}
