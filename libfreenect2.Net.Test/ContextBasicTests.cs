using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace libfreenect2Net.Test
{
    [TestClass]
    public class ContextBasicTests
    {
        [TestMethod]
        public void ShouldCreateAndDisposeContext()
        {
            var context = new Context();
            context.Should().NotBeNull();
            context.IsDisposed.Should().BeFalse();

            context.Dispose();
            context.IsDisposed.Should().BeTrue();
        }

        [TestMethod]
        public void ShouldAllowCreateMultipleContexts()
        {
            using (var context1 = new Context())
            using (var context2 = new Context())
            {
            }
        }
    }
}
