#include "Registration.h"

using namespace System;

namespace libfreenect2Net
{
	Registration::Registration(InfraRedCameraParameters infraredParams, ColorCameraParameters colorParams)
		: ManagedWrapper(new libfreenect2::Registration(infraredParams, colorParams))
	{
	}

	void Registration::ApplyToPoint(int dx, int dy, float dz, [Out] float% cx, [Out] float% cy)
	{
		float cxLocal, cyLocal;
		Instance->apply(dx, dy, dz, cxLocal, cyLocal);
		cx = cxLocal;
		cy = cyLocal;
	}

	void Registration::Apply(Frame^ rgb, Frame^ depth, Frame^ undistorted, Frame^ registered, [Optional] bool disableFilter, [Optional] Frame^ registeredInverse, [Optional] array<int>^ colorDepthMap)
	{
		if (ReferenceEquals(rgb, nullptr))
			throw gcnew ArgumentNullException("rgb");

		if (ReferenceEquals(depth, nullptr))
			throw gcnew ArgumentNullException("depth");

		if (ReferenceEquals(undistorted, nullptr))
			throw gcnew ArgumentNullException("undistorted");

		if (ReferenceEquals(registered, nullptr))
			throw gcnew ArgumentNullException("registered");

		pin_ptr<int> colorDepthMapPtr = nullptr;
		if (!ReferenceEquals(colorDepthMap, nullptr))
		{
			colorDepthMapPtr = &colorDepthMap[0];
		}

		Instance->apply(rgb, depth, undistorted, registered, !disableFilter, registeredInverse, colorDepthMapPtr);
	}

	void Registration::UndistortDepth(Frame^ depth, Frame^ undistorted)
	{
		Instance->undistortDepth(depth, undistorted);
	}

	void Registration::GetPoint(Frame^ undistorted, Frame^ registered, int r, int c, [Out] float% x, [Out] float% y, [Out] float% z, [Out] int% bgrx)
	{
		if (ReferenceEquals(undistorted, nullptr))
			throw gcnew ArgumentNullException("undistorted");

		if (ReferenceEquals(registered, nullptr))
			throw gcnew ArgumentNullException("registered");

		float xLocal, yLocal, zLocal;
		float bgrxPacked;
		Instance->getPointXYZRGB(undistorted, registered, r, c, xLocal, yLocal, zLocal, bgrxPacked);

		x = xLocal;
		y = yLocal;
		z = zLocal;
		// Assume little-endian platform
		bgrx = *(reinterpret_cast<int*>(&bgrxPacked));
	}

	void Registration::GetPoint(Frame^ undistorted, int r, int c, [Out] float% x, [Out] float% y, [Out] float% z)
	{
		if (ReferenceEquals(undistorted, nullptr))
			throw gcnew ArgumentNullException("undistorted");

		float xLocal, yLocal, zLocal;
		Instance->getPointXYZ(undistorted, r, c, xLocal, yLocal, zLocal);

		x = xLocal;
		y = yLocal;
		z = zLocal;
	}
}