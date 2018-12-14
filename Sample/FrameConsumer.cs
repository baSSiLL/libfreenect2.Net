using libfreenect2Net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace Sample
{
    internal abstract class FrameConsumer
    {
        private readonly object _sync = new object();
        private readonly FrameQueue _queue;
        private readonly FrameType[] _frameTypes;
        private bool _working;

        protected FrameConsumer(FrameQueue queue, params FrameType[] frameTypes)
        {
            _queue = queue;
            _frameTypes = frameTypes;
        }

        public void Start()
        {
            lock (_sync) _working = true;

            _queue.NewFrameArrived += OnNewFrameArrived;
            if (_frameTypes.All(_queue.HasPendingFrames))
            {
                ScheduleTryStartProcessingNewFrames();
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

        protected abstract void StartProcessing(IReadOnlyDictionary<FrameType, Frame> frames);

        protected virtual void OnProcessingFinished(IReadOnlyDictionary<FrameType, Frame> frames)
        {
            foreach (var f in frames.Values)
            {
                f.Dispose();
            }
            IsProcessing = false;

            ScheduleTryStartProcessingNewFrames();
        }

        private void OnNewFrameArrived(object sender, EventArgs e)
        {
            if (!IsProcessing)
            {
                ScheduleTryStartProcessingNewFrames();
            }
        }

        private void ScheduleTryStartProcessingNewFrames()
        {
            ThreadPool.QueueUserWorkItem(_ => TryStartProcessingNewFrames());
        }

        private void TryStartProcessingNewFrames()
        {
            IReadOnlyDictionary<FrameType, Frame> toProcess = null;
            lock (_sync)
            {
                if (_working && !IsProcessing)
                {
                    // Simply take the latest frames of all types
                    // For real life scenarios some kind of inter-frame synchronization
                    // should be added, e.g. based on their timestamps
                    if (_frameTypes.All(_queue.HasPendingFrames))
                    {
                        toProcess = _frameTypes.ToDictionary(ft => ft, _queue.DequeueLatestAndDiscardPrevious);
                        if (toProcess != null)
                        {
                            IsProcessing = true;
                        }
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
