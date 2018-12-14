using libfreenect2Net;
using System.Collections.Generic;

namespace Sample
{
    internal class DummyFrameConsumer : FrameConsumer
    {
        public DummyFrameConsumer(FrameQueue queue, params FrameType[] frameTypes) 
            : base(queue, frameTypes)
        {
        }

        protected override void StartProcessing(IReadOnlyDictionary<FrameType, Frame> frames)
        {
            OnProcessingFinished(frames);
        }
    }
}
