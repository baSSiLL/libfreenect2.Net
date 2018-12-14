#pragma once

#define CAST_TO_MANAGED(ClassName, instance) ((instance) == nullptr ? nullptr : gcnew ClassName(instance))

using namespace System;

namespace libfreenect2Net
{
	namespace Internals
	{
		private ref class Checks abstract sealed
		{
		public:
			static int IsPositive(int value, String^ paramName)
			{
				if (value <= 0)
					throw gcnew ArgumentOutOfRangeException(paramName, "Expecting positive value");

				return value;
			}
		};
	}
}