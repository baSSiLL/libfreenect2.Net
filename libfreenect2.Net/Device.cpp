#include "Device.h"

namespace libfreenect2Net
{
	Device::Device(libfreenect2::Freenect2Device* instance)
		: ManagedWrapper(instance)
	{
	}

	Device::operator Device^ (libfreenect2::Freenect2Device* instance)
	{
		return instance == nullptr ? nullptr : gcnew Device(instance);
	}
}