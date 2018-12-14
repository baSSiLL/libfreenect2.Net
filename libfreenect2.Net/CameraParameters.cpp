#include "CameraParameters.h"

namespace libfreenect2Net
{
	ColorCameraParameters::operator libfreenect2::Freenect2Device::ColorCameraParams(ColorCameraParameters value)
	{
		libfreenect2::Freenect2Device::ColorCameraParams result;

		result.fx = value.FocalLengthX;
		result.fy = value.FocalLengthY;
		result.cx = value.PrincipalPointX;
		result.cy = value.PrincipalPointY;

		result.shift_d = value.Extrinsics.shift_d;
		result.shift_m = value.Extrinsics.shift_m;

		result.mx_x3y0 = value.Extrinsics.mx_x3y0;
		result.mx_x0y3 = value.Extrinsics.mx_x0y3;
		result.mx_x2y1 = value.Extrinsics.mx_x2y1;
		result.mx_x1y2 = value.Extrinsics.mx_x1y2;
		result.mx_x2y0 = value.Extrinsics.mx_x2y0;
		result.mx_x0y2 = value.Extrinsics.mx_x0y2;
		result.mx_x1y1 = value.Extrinsics.mx_x1y1;
		result.mx_x1y0 = value.Extrinsics.mx_x1y0;
		result.mx_x0y1 = value.Extrinsics.mx_x0y1;
		result.mx_x0y0 = value.Extrinsics.mx_x0y0;

		result.my_x3y0 = value.Extrinsics.my_x3y0;
		result.my_x0y3 = value.Extrinsics.my_x0y3;
		result.my_x2y1 = value.Extrinsics.my_x2y1;
		result.my_x1y2 = value.Extrinsics.my_x1y2;
		result.my_x2y0 = value.Extrinsics.my_x2y0;
		result.my_x0y2 = value.Extrinsics.my_x0y2;
		result.my_x1y1 = value.Extrinsics.my_x1y1;
		result.my_x1y0 = value.Extrinsics.my_x1y0;
		result.my_x0y1 = value.Extrinsics.my_x0y1;
		result.my_x0y0 = value.Extrinsics.my_x0y0;

		return result;
	}

	ColorCameraParameters::operator ColorCameraParameters(const libfreenect2::Freenect2Device::ColorCameraParams& value)
	{
		ColorCameraParameters result;

		result.FocalLengthX = value.fx;
		result.FocalLengthY = value.fy;
		result.PrincipalPointX = value.cx;
		result.PrincipalPointY = value.cy;

		result.Extrinsics.shift_d = value.shift_d;
		result.Extrinsics.shift_m = value.shift_m;

		result.Extrinsics.mx_x3y0 = value.mx_x3y0;
		result.Extrinsics.mx_x0y3 = value.mx_x0y3;
		result.Extrinsics.mx_x2y1 = value.mx_x2y1;
		result.Extrinsics.mx_x1y2 = value.mx_x1y2;
		result.Extrinsics.mx_x2y0 = value.mx_x2y0;
		result.Extrinsics.mx_x0y2 = value.mx_x0y2;
		result.Extrinsics.mx_x1y1 = value.mx_x1y1;
		result.Extrinsics.mx_x1y0 = value.mx_x1y0;
		result.Extrinsics.mx_x0y1 = value.mx_x0y1;
		result.Extrinsics.mx_x0y0 = value.mx_x0y0;

		result.Extrinsics.my_x3y0 = value.my_x3y0;
		result.Extrinsics.my_x0y3 = value.my_x0y3;
		result.Extrinsics.my_x2y1 = value.my_x2y1;
		result.Extrinsics.my_x1y2 = value.my_x1y2;
		result.Extrinsics.my_x2y0 = value.my_x2y0;
		result.Extrinsics.my_x0y2 = value.my_x0y2;
		result.Extrinsics.my_x1y1 = value.my_x1y1;
		result.Extrinsics.my_x1y0 = value.my_x1y0;
		result.Extrinsics.my_x0y1 = value.my_x0y1;
		result.Extrinsics.my_x0y0 = value.my_x0y0;

		return result;
	}

	InfraRedCameraParameters::operator libfreenect2::Freenect2Device::IrCameraParams(InfraRedCameraParameters value)
	{
		libfreenect2::Freenect2Device::IrCameraParams result;

		result.fx = value.FocalLengthX;
		result.fy = value.FocalLengthY;
		result.cx = value.PrincipalPointX;
		result.cy = value.PrincipalPointY;

		result.k1 = value.Distortion.K1;
		result.k2 = value.Distortion.K2;
		result.k3 = value.Distortion.K3;

		result.p1 = value.Distortion.P1;
		result.p2 = value.Distortion.P2;

		return result;
	}

	InfraRedCameraParameters::operator InfraRedCameraParameters(const libfreenect2::Freenect2Device::IrCameraParams& value)
	{
		libfreenect2Net::InfraRedCameraParameters result;

		result.FocalLengthX = value.fx;
		result.FocalLengthY = value.fy;
		result.PrincipalPointX = value.cx;
		result.PrincipalPointY = value.cy;

		result.Distortion.K1 = value.k1;
		result.Distortion.K2 = value.k2;
		result.Distortion.K3 = value.k3;

		result.Distortion.P1 = value.p1;
		result.Distortion.P2 = value.p2;

		return result;
	}
}