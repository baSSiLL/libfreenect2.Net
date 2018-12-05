using libfreenect2Net;
using System;
using System.Diagnostics;

namespace Sample
{
    internal class FrameListener : IFrameListener
    {
        private static readonly TimeSpan LogInterval = TimeSpan.FromSeconds(0.5);

        private readonly FrameQueue _queue;
        private readonly Action<string> _logger;
        private readonly Stopwatch _stopwatch;
        private long _colorCount = 0;
        private long _depthCount = 0;
        private long _infraRedCount = 0;
        private long _errors = 0;

        public FrameListener(FrameQueue queue, Action<string> logger)
        {
            _queue = queue;
            _logger = logger;
            _stopwatch = Stopwatch.StartNew();
        }

        public bool OnNewFrame(FrameType frameType, Frame frame)
        {
            var reportToLog = false;
            long colorCount, depthCount, infraRedCount, errors;
            lock (_stopwatch)
            {
                switch (frameType)
                {
                    case FrameType.Color:
                        _colorCount++;
                        break;
                    case FrameType.Depth:
                        _depthCount++;
                        break;
                    case FrameType.InfraRed:
                        _infraRedCount++;
                        break;
                }
                if (frame.HasError) _errors++;

                colorCount = _colorCount;
                depthCount = _depthCount;
                infraRedCount = _infraRedCount;
                errors = _errors;

                if (_stopwatch.Elapsed >= LogInterval)
                {
                    reportToLog = true;
                    _stopwatch.Restart();
                }
            }

            if (reportToLog)
            {
                var message = $"Recent frame: type={frameType}, data format={frame.DataFormat}, timestamp={frame.TimeStamp}, sequence={frame.Sequence}, width={frame.Width}, height={frame.Height}, bpp={frame.BytesPerPixel}, has error={frame.HasError}";
                _logger.Invoke(message);
                message = $"Total frames received: color={colorCount}, depth={depthCount}, infra red={infraRedCount}, errors={errors}";
                _logger.Invoke(message);
            }

            if (!frame.HasError)
            {
                _queue.Enqueue(frameType, frame);
            }

            return true;
        }
    }
}
