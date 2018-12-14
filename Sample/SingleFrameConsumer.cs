using libfreenect2Net;
using System.Collections.Generic;
using System.Linq;

namespace Sample
{
    internal abstract class SingleFrameConsumer : FrameConsumer
    {
        private readonly FrameType _frameType;

        protected SingleFrameConsumer(FrameQueue queue, FrameType frameType)
            : base(queue, frameType)
        {
            _frameType = frameType;
        }

        protected abstract void StartProcessing(Frame frame);

        protected sealed override void StartProcessing(IReadOnlyDictionary<FrameType, Frame> frames)
        {
            StartProcessing(frames.Values.Single());
        }

        protected virtual void OnProcessingFinished(Frame frame)
        {
            OnProcessingFinished(new Dictionary<FrameType, Frame> { [_frameType] = frame });
        }

        protected sealed override void OnProcessingFinished(IReadOnlyDictionary<FrameType, Frame> frames)
        {
            base.OnProcessingFinished(frames);
        }
    }
}
