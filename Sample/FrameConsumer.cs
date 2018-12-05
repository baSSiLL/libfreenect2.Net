using libfreenect2Net;
using System;
using System.Threading;

namespace Sample
{
    internal abstract class FrameConsumer
    {
        private readonly object _sync = new object();
        private readonly FrameQueue _queue;
        private readonly FrameType _frameType;
        private bool _working;

        protected FrameConsumer(FrameQueue queue, FrameType frameType)
        {
            _queue = queue;
            _frameType = frameType;
        }

        public void Start()
        {
            lock (_sync) _working = true;

            _queue.NewFrameArrived += OnNewFrameArrived;
            if (_queue.HasPendingFrames(_frameType))
            {
                ScheduleTryStartProcessingNewFrame();
            }
        }

        public void Stop()
        {
            lock (_sync) _working = false;
        }

        protected bool IsProcessing
        {
            get { lock (_sync) return _isProcessing; }
            private set => _isProcessing = value;
        }
        private bool _isProcessing;

        protected virtual void StartProcessing(Frame frame)
        {
        }

        protected virtual void OnProcessingFinished(Frame frame)
        {
            frame.Dispose();
            IsProcessing = false;

            ScheduleTryStartProcessingNewFrame();
        }

        private void OnNewFrameArrived(object sender, EventArgs e)
        {
            if (!IsProcessing)
            {
                ScheduleTryStartProcessingNewFrame();
            }
        }

        private void ScheduleTryStartProcessingNewFrame()
        {
            ThreadPool.QueueUserWorkItem(_ => TryStartProcessingNewFrame());
        }

        private void TryStartProcessingNewFrame()
        {
            Frame toProcess = null;
            lock (_sync)
            {
                if (_working && !IsProcessing)
                {
                    toProcess = _queue.DequeueLatestAndDiscardPrevious(_frameType);
                    if (toProcess != null)
                    {
                        IsProcessing = true;
                    }
                }
            }

            if (toProcess != null)
            {
                StartProcessing(toProcess);
            }
        }
    }
}
