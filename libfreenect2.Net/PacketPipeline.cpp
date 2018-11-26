#include "PacketPipeline.h"

namespace libfreenect2Net
{
	PacketPipeline::PacketPipeline(libfreenect2::PacketPipeline* instance)
		: ManagedWrapper(instance)
	{
	}

	PacketPipeline::operator PacketPipeline^ (libfreenect2::PacketPipeline* instance)
	{
		return instance == nullptr ? nullptr : gcnew PacketPipeline(instance);
	}
}