using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace libfreenect2Net.Test
{
    [TestClass]
    public class StreamingTests : TestClassWithContext
    {
        public Device DefaultDevice { get; set; }
        public bool IsDeviceOpen => DefaultDevice != null;

        [TestInitialize]
        public void OpenDevice()
        {
            DefaultDevice = Context.OpenDefaultDevice();
        }

        [TestCleanup]
        public void DisposeDevice()
        {
            DefaultDevice?.Dispose();
        }

        [TestMethod]
        public void ShouldStartAllAndStop()
        {
            if (IsDeviceOpen)
            {
                var started = DefaultDevice.StartAll();
                var stopped = DefaultDevice.Stop();

                started.Should().BeTrue();
                stopped.Should().BeTrue();
            }
        }

        [TestMethod]
        public void ShouldStartColorAndStop()
        {
            if (IsDeviceOpen)
            {
                var started = DefaultDevice.StartColor();
                var stopped = DefaultDevice.Stop();

                started.Should().BeTrue();
                stopped.Should().BeTrue();
            }
        }

        [TestMethod]
        public void ShouldStartDepthAndStop()
        {
            if (IsDeviceOpen)
            {
                var started = DefaultDevice.StartDepth();
                var stopped = DefaultDevice.Stop();

                started.Should().BeTrue();
                stopped.Should().BeTrue();
            }
        }

        [TestMethod]
        public void ShouldReturnFirmwareVersionAfterStart()
        {
            if (IsDeviceOpen)
            {
                DefaultDevice.StartAll();
                var firmwareVersion = DefaultDevice.FirmwareVersion;
                DefaultDevice.Stop();

                firmwareVersion.Should().NotBeNullOrEmpty();
            }
        }

        [TestMethod]
        public void ShouldGetColorAndDepthAndIRFramesWhenStartAll()
        {
            // Currently cannot test any code involving unmanaged->managed interop
            // because of "Cannot pass a GCHandle across AppDomains" error
            // (MSUnit test runner creates a separate AppDomain for each test container)

            //var listener = new CountingFrameListener();
            //DefaultDevice.SetColorListener(listener);
            //DefaultDevice.SetDepthListener(listener);
            //DefaultDevice.StartAll();
            //Thread.Sleep(1000);
            //DefaultDevice.Stop();

            //listener.ColorCount.Should().BePositive();
            //listener.DepthCount.Should().BePositive();
            //listener.InfraRedCount.Should().BePositive();
            //listener.InfraRedCount.Should().BeCloseTo(listener.DepthCount, 1);
        }


        private class CountingFrameListener : IFrameListener
        {
            public int ColorCount => _colorCount;
            int _colorCount;

            public int DepthCount => _depthCount;
            int _depthCount;

            public int InfraRedCount => _irCount;
            int _irCount;

            public bool OnNewFrame(FrameType frameType, Frame frame)
            {
                switch (frameType)
                {
                    case FrameType.Color:
                        Interlocked.Increment(ref _colorCount);
                        break;
                    case FrameType.Depth:
                        Interlocked.Increment(ref _depthCount);
                        break;
                    case FrameType.InfraRed:
                        Interlocked.Increment(ref _irCount);
                        break;
                }

                return false;
            }
        }
    }
}
