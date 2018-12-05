using libfreenect2Net;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace Sample
{
    internal class FrameQueue : IDisposable
    {
        private readonly IReadOnlyDictionary<FrameType, ConcurrentQueue<Frame>> _queues =
            Enum.GetValues(typeof(FrameType)).Cast<FrameType>().
            ToDictionary(ft => ft, _ => new ConcurrentQueue<Frame>());

        private bool IsDisposed
        {
            get { lock (_queues) return _isDisposed; }
            set { lock (_queues) _isDisposed = value; }
        }
        private bool _isDisposed;

        public event EventHandler NewFrameArrived;

        public void Enqueue(FrameType frameType, Frame newFrame)
        {
            if (IsDisposed)
                throw new ObjectDisposedException(nameof(FrameQueue));

            _queues[frameType].Enqueue(newFrame);
            NewFrameArrived?.Invoke(this, EventArgs.Empty);
        }

        public bool HasPendingFrames(FrameType frameType) => _queues[frameType].Count > 0;

        public Frame DequeueLatestAndDiscardPrevious(FrameType frameType)
        {
            var queue = _queues[frameType];
            Frame latest = null;
            while (queue.TryDequeue(out var result))
            {
                latest?.Dispose();
                latest = result;
            }
            return latest;
        }

        public void Dispose()
        {
            IsDisposed = true;
            foreach (var f in _queues.Values.SelectMany(q => q))
            {
                f.Dispose();
            }
        }
    }
}
