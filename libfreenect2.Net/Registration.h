#pragma once

#include <libfreenect2\registration.h>
#include "ManagedWrapper.h"
#include "CameraParameters.h"
#include "Frame.h"

using namespace System::Runtime::InteropServices;

namespace libfreenect2Net
{
	public ref class Registration : public Internals::ManagedWrapper<libfreenect2::Registration>
	{
	public:
		Registration(InfraRedCameraParameters infraredParams, ColorCameraParameters colorParams);

		/// <summary>Undistort and register a single depth point to color camera.</summary>
		/// <param name="dx">Distorted depth coordinate x (pixel)</param>
		/// <param name="dy">Distorted depth coordinate y (pixel)</param>
		/// <param name="dz">Depth value (millimeter)</param>
		/// <param name="cx">Undistorted color coordinate x (normalized)</param>
		/// <param name="cy">Undistorted color coordinate y (normalized)</param>
		void ApplyToPoint(int dx, int dy, float dz, [Out] float% cx, [Out] float% cy);

		/// <summary>Map color images onto depth images.</summary>
		/// <param name="rgb">Color image (1920x1080 BGRX)</param>
		/// <param name="depth">Depth image (512x424 float)</param>
		/// <param name="undistorted">Undistorted depth image</param>
		/// <param name="registered">Color image for the depth image (512x424)</param>
		/// <param name="disableFilter">Do not filter out pixels not visible to both cameras.</param>
		/// <param name="registeredInverse">When not <c>null</c>, gets depth values for the color image (1920x1082 float). **1082** not 1080, with a blank top and bottom row.</param>
		/// <param name="colorDepthMap">Index of mapped color pixel for each depth pixel (512x424).</param>
		void Apply(Frame^ rgb, Frame^ depth, Frame^ undistorted, Frame^ registered, [Optional] bool disableFilter, [Optional] Frame^ registeredInverse, [Optional] array<int>^ colorDepthMap);

		/// <summary>Undistort depth.</summary>
		/// <param name="depth">Depth image (512x424 float)</param>
		/// <param name="undistorted">Undistorted depth image</param>
		void UndistortDepth(Frame^ depth, Frame^ undistorted);

		/// <summary>Construct a 3-D point with color in a point cloud.</summary>
		/// <param name="undistorted">Undistorted depth frame from <see cref="Apply"/>.</param>
		/// <param name="registered">Registered color frame from <see cref="Apply"/>.</param>
		/// <param name="r">Row (y) index in depth image.</param>
		/// <param name="c">Column (x) index in depth image.</param>
		/// <param name="x">X coordinate of the 3-D point (meter).</param>
		/// <param name="y">Y coordinate of the 3-D point (meter).</param>
		/// <param name="z">Z coordinate of the 3-D point (meter).</param>
		/// <param name="bgrx">Color of the 3-D point (BGRX).</param>
		void GetPoint(Frame^ undistorted, Frame^ registered, int r, int c, [Out] float% x, [Out] float% y, [Out] float% z, [Out] int% bgrx);

		/// <summary>Construct a 3-D point in a point cloud.</summary>
		/// <param name="undistorted">Undistorted depth frame from <see cref="Apply"/>.</param>
		/// <param name="r">Row (y) index in depth image.</param>
		/// <param name="c">Column (x) index in depth image.</param>
		/// <param name="x">X coordinate of the 3-D point (meter).</param>
		/// <param name="y">Y coordinate of the 3-D point (meter).</param>
		/// <param name="z">Z coordinate of the 3-D point (meter).</param>
		void GetPoint(Frame^ undistorted, int r, int c, [Out] float% x, [Out] float% y, [Out] float% z);
	};
}