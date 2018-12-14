using libfreenect2Net;
using System.Collections.Generic;

namespace Sample
{
    internal class FrameRegistrationProcessor : FrameConsumer
    {
        private readonly FrameQueue _outQueue;
        private readonly Registration _registration;

        public FrameRegistrationProcessor(FrameQueue inQueue, FrameQueue outQueue, Registration registration)
            : base(inQueue, FrameType.Depth, FrameType.Color)
        {
            _outQueue = outQueue;
            _registration = registration;
        }

        protected override void StartProcessing(IReadOnlyDictionary<FrameType, Frame> frames)
        {
            var depthFrame = frames[FrameType.Depth];
            var undistorted = new Frame(depthFrame.Width, depthFrame.Height, FrameDataFormat.Float);
            var registered = new Frame(depthFrame.Width, depthFrame.Height, FrameDataFormat.Bgrx);
            _registration.Apply(frames[FrameType.Color], depthFrame, undistorted, registered);

            _outQueue.Enqueue(FrameType.Depth, undistorted);
            _outQueue.Enqueue(FrameType.Color, registered);

            OnProcessingFinished(frames);
        }
    }
}
