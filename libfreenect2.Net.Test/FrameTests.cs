using System;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace libfreenect2Net.Test
{
    [TestClass]
    public class FrameTests
    {
        [TestMethod]
        [DataRow(1920, 1080, FrameDataFormat.Bgrx, 4)]
        [DataRow(1920, 1082, FrameDataFormat.Rgbx, 4)]
        [DataRow(512, 424, FrameDataFormat.Float, 4)]
        [DataRow(512, 424, FrameDataFormat.Gray, 1)]
        public void ShouldCreateValidFrames(int width, int height, FrameDataFormat format, int bpp)
        {
            using (var frame = new Frame(width, height, format))
            {
                frame.Width.Should().Be(width);
                frame.Height.Should().Be(height);
                frame.DataFormat.Should().Be(format);
                frame.BytesPerPixel.Should().Be(bpp);
                frame.Data.Should().NotBe(IntPtr.Zero);
                frame.DataSize.Should().Be(width * height * bpp);
            }
        }

        [TestMethod]
        [DataRow(0)]
        [DataRow(-1920)]
        [DataRow(-512)]
        public void ShouldNotCreateWithInvalidWidth(int width)
        {
            Action create = () => new Frame(width, 1, FrameDataFormat.Bgrx);

            create.Should().Throw<ArgumentOutOfRangeException>().
                And.ParamName.Should().Be("width");
        }

        [TestMethod]
        [DataRow(0)]
        [DataRow(-1080)]
        [DataRow(-424)]
        public void ShouldNotCreateWithInvalidHeight(int height)
        {
            Action create = () => new Frame(1, height, FrameDataFormat.Bgrx);

            create.Should().Throw<ArgumentOutOfRangeException>().
                And.ParamName.Should().Be("height");
        }

        [TestMethod]
        [DataRow(FrameDataFormat.Raw)]
        [DataRow(FrameDataFormat.Invalid)]
        public void ShouldNotCreateWithInvalidFormat(FrameDataFormat format)
        {
            Action create = () => new Frame(1, 1, format);

            create.Should().Throw<ArgumentOutOfRangeException>().
                And.ParamName.Should().Be("dataFormat");
        }
    }
}
