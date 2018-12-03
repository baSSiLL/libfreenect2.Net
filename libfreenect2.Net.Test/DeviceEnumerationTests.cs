using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace libfreenect2Net.Test
{
    [TestClass]
    public class DeviceEnumerationTests : TestClassWithContext
    {
        public TestContext TestContext { get; set; }

        [TestMethod]
        public void ShouldReturnNonNegativeOnEnumerateDevices()
        {
            var deviceCount = Context.EnumerateDevices();
            deviceCount.Should().BeGreaterOrEqualTo(0);

            TestContext.WriteLine("Enumerated {0} devices", deviceCount);
        }

        [TestMethod]
        public void ShouldReturnSerialForAllEnumeratedDevices()
        {
            var deviceCount = Context.EnumerateDevices();
            for (var i = 0; i < deviceCount; i++)
            {
                var serial = Context.GetDeviceSerialNumber(i);
                serial.Should().NotBeNullOrEmpty("Current device index = {0}", i);
            }
        }
    }
}
