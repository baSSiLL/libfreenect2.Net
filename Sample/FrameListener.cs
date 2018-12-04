using libfreenect2Net;
using System;
using System.Diagnostics;

namespace Sample
{
    internal class FrameListener : IFrameListener
    {
        private static readonly TimeSpan LogInterval = TimeSpan.FromSeconds(0.5);

        private readonly Action<string> _logger;
        private readonly Stopwatch _stopwatch;
        private long _colorCount = 0;
        private long _depthCount = 0;
        private long _infraRedCount = 0;

        public FrameListener(Action<string> logger)
        {
            _logger = logger;
            _stopwatch = Stopwatch.StartNew();
        }

        public bool OnNewFrame(FrameType frameType, Frame frame)
        {
            var reportToLog = false;
            long colorCount, depthCount, infraRedCount;
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
                colorCount = _colorCount;
                depthCount = _depthCount;
                infraRedCount = _infraRedCount;

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
                message = $"Total frames received: color={colorCount}, depth={depthCount}, infra red={infraRedCount}";
                _logger.Invoke(message);
            }

            return false;
        }
    }
}
