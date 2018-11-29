#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"

namespace libfreenect2Net
{
	public ref class Frame : public Internals::ManagedWrapper<libfreenect2::Frame>
	{
	private:
		Frame(libfreenect2::Frame* instance);

	internal:
		static explicit operator Frame^ (libfreenect2::Frame* instance);
	};
}