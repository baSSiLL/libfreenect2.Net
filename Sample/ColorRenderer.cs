using libfreenect2Net;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Sample
{
    internal class ColorRenderer : SingleFrameConsumer
    {
        private readonly WriteableBitmap _bitmap;

        public ColorRenderer(FrameQueue queue, WriteableBitmap bitmap) 
            : base(queue, FrameType.Color)
        {
            _bitmap = bitmap;
        }

        protected override void StartProcessing(Frame frame)
        {
            _bitmap.Dispatcher.BeginInvoke(new Action<Frame>(RenderFrame), frame);
        }

        private void RenderFrame(Frame frame)
        {
            var formatMatches = frame.DataFormat == FrameDataFormat.Bgrx && _bitmap.Format == PixelFormats.Bgr32 ||
                frame.DataFormat == FrameDataFormat.Gray && _bitmap.Format == PixelFormats.Gray8;
            var sizeMatches = frame.Width == _bitmap.PixelWidth && frame.Height == _bitmap.PixelHeight;
            if (formatMatches && sizeMatches)
            {
                var rect = new Int32Rect(0, 0, frame.Width, frame.Height);
                _bitmap.WritePixels(rect, frame.Data, 
                    frame.DataSize, 
                    frame.Width * frame.BytesPerPixel);
            }

            ThreadPool.QueueUserWorkItem(f => OnProcessingFinished((Frame)f), frame);
        }
    }
}
