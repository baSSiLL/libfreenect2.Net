#include "PacketPipeline.h"
#include "Implementation.h"

namespace libfreenect2Net
{
	PacketPipeline::PacketPipeline(libfreenect2::PacketPipeline* instance)
		: ManagedWrapper(instance)
	{
	}

	PacketPipeline::operator PacketPipeline^ (libfreenect2::PacketPipeline* instance)
	{
		return CAST_TO_MANAGED(PacketPipeline, instance);
	}
}