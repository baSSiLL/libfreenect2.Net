using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace libfreenect2Net.Test
{
    [TestClass]
    public class CameraParametersTests : TestClassWithContext
    {
        [TestMethod]
        public void InfraRedParamsShouldHaveReasonableValues()
        {
            using (var device = Context.OpenDefaultDevice())
            {
                if (device != null)
                {
                    device.StartAll();
                    var p = device.InfraRedCameraParameters;
                    var fovXDegrees = 2 * Math.Atan2(256, p.FocalLengthX) * 180 / Math.PI;
                    var fovYDegrees = 2 * Math.Atan2(212, p.FocalLengthY) * 180 / Math.PI;
                    device.Stop();

                    fovXDegrees.Should().BeApproximately(70, 1);
                    fovYDegrees.Should().BeApproximately(60, 1);
                    p.PrincipalPointX.Should().BeApproximately(256, 10);
                    p.PrincipalPointY.Should().BeApproximately(212, 10);
                }
            }
        }

        [TestMethod]
        public void ColorParamsShouldHaveReasonableValues()
        {
            using (var device = Context.OpenDefaultDevice())
            {
                if (device != null)
                {
                    device.StartAll();
                    var p = device.ColorCameraParameters;
                    var fovXDegrees = 2 * Math.Atan2(960, p.FocalLengthX) * 180 / Math.PI;
                    var fovYDegrees = 2 * Math.Atan2(540, p.FocalLengthY) * 180 / Math.PI;
                    device.Stop();

                    fovXDegrees.Should().BeApproximately(83.5, 1);
                    fovYDegrees.Should().BeApproximately(53.5, 1);
                    p.PrincipalPointX.Should().BeApproximately(960, 15);
                    p.PrincipalPointY.Should().BeApproximately(540, 15);
                }
            }
        }
    }
}
