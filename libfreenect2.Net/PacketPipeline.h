#pragma once

#include <libfreenect2\libfreenect2.hpp>
#include "ManagedWrapper.h"

namespace libfreenect2Net
{
	public ref class PacketPipeline : public Internals::ManagedWrapper<libfreenect2::PacketPipeline>
	{
	internal:
		PacketPipeline(libfreenect2::PacketPipeline* instance);
	};
}