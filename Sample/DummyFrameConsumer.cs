using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using libfreenect2Net;

namespace Sample
{
    internal class DummyFrameConsumer : FrameConsumer
    {
        public DummyFrameConsumer(FrameQueue queue, FrameType frameType) 
            : base(queue, frameType)
        {
        }

        protected override void StartProcessing(Frame frame)
        {
            base.StartProcessing(frame);
            OnProcessingFinished(frame);
        }
    }
}
