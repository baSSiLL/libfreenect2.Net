#include "PacketPipeline.h"

namespace libfreenect2Net
{
	PacketPipeline::PacketPipeline(libfreenect2::PacketPipeline* instance)
		: ManagedWrapper(instance)
	{
	}
}