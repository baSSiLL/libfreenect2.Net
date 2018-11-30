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
		/// <summary>Executed when a new frame arrives.</summary>
		/// <returns>Indicates whether a callee took ownership of the frame.</returns>
		/// <remarks>
		/// When the method returns <c>true</c> this implies that the callee won't be using this frame any further.
		/// For instance, it has been ignored or its data have been already processed or copied.
		/// Otherwise, the callee takes responsibility to dispose the frame later when it's not needed anymore.
		/// </remarks>
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

