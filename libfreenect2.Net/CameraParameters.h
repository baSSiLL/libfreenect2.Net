#pragma once

namespace libfreenect2Net
{
	/// <summary>Extrinsic camera parameters used for depth-to-color coordinate mapping.</summary>
	/// <remarks>
	/// See the formula used for calculations 
	/// <see cref="https://github.com/OpenKinect/libfreenect2/issues/41#issuecomment-72022111"/>.
	/// </remarks>
	public value class ExtrinsicCameraParameters
	{
	public:
		float shift_d, shift_m;

		float mx_x3y0; // xxx
		float mx_x0y3; // yyy
		float mx_x2y1; // xxy
		float mx_x1y2; // yyx
		float mx_x2y0; // xx
		float mx_x0y2; // yy
		float mx_x1y1; // xy
		float mx_x1y0; // x
		float mx_x0y1; // y
		float mx_x0y0; // 1

		float my_x3y0; // xxx
		float my_x0y3; // yyy
		float my_x2y1; // xxy
		float my_x1y2; // yyx
		float my_x2y0; // xx
		float my_x0y2; // yy
		float my_x1y1; // xy
		float my_x1y0; // x
		float my_x0y1; // y
		float my_x0y0; // 1
	};

	public value class ColorCameraParameters
	{
	public:
		/// <summary>Focal length X, in pixels.</summary>
		float FocalLengthX;

		/// <summary>Focal length Y, in pixels.</summary>
		float FocalLengthY;

		/// <summary>Principal point X, in pixels.</summary>
		float PrincipalPointX;

		/// <summary>Principal point Y, in pixels.</summary>
		float PrincipalPointY;

		/// <summary>Extrinsic parameters.</summary>
		ExtrinsicCameraParameters Extrinsics;
	};

	/// <summary>Parameters of image distortion introduced by infrared sensor.</summary>
	public value class InfraRedCameraDistortion
	{
	public:
		/// <summary>Radial distortion coefficient, 1st order.</summary>
		float K1;

		/// <summary>Radial distortion coefficient, 2nd order.</summary>
		float K2;

		/// <summary>Radial distortion coefficient, 3rd order.</summary>
		float K3;

		/// <summary>Tangential distortion coefficient.</summary>
		float P1;

		/// <summary>Tangential distortion coefficient.</summary>
		float P2;
	};

	public value class InfraRedCameraParameters
	{
	public:
		/// <summary>Focal length X, in pixels.</summary>
		float FocalLengthX;

		/// <summary>Focal length Y, in pixels.</summary>
		float FocalLengthY;

		/// <summary>Principal point X, in pixels.</summary>
		float PrincipalPointX;

		/// <summary>Principal point Y, in pixels.</summary>
		float PrincipalPointY;

		/// <summary>Parameters of distortion.</summary>
		InfraRedCameraDistortion Distortion;
	};
}
