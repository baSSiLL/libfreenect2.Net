#include "Frame.h"
#include "Implementation.h"

namespace libfreenect2Net
{
	Frame::Frame(libfreenect2::Frame* instance)
		: ManagedWrapper(instance)
	{
	}

	Frame::operator libfreenect2Net::Frame ^ (libfreenect2::Frame* instance)
	{
		return CAST_TO_MANAGED(Frame, instance);
	}
}