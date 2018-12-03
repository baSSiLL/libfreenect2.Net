using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace libfreenect2Net.Test
{
    public abstract class TestClassWithContext
    {
        protected TestClassWithContext()
        {
        }

        protected Context Context { get; set; }

        [TestInitialize]
        public void CreateContext()
        {
            Context = new Context();
        }

        [TestCleanup]
        public void DisposeContext()
        {
            Context.Dispose();
        }
    }
}
