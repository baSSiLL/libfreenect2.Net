using libfreenect2Net;
using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;

namespace Sample
{
    internal class DepthRenderer : FrameConsumer
    {
        private readonly WriteableBitmap _bitmap;
        private readonly byte[] _pixels;

        public DepthRenderer(FrameQueue queue, WriteableBitmap bitmap) 
            : base(queue, FrameType.Depth)
        {
            _bitmap = bitmap;
            _pixels = new byte[_bitmap.PixelWidth * _bitmap.PixelHeight];
        }

        protected override void StartProcessing(Frame frame)
        {
            base.StartProcessing(frame);

            var task = RenderFrameAsync(frame);
        }

        private async Task RenderFrameAsync(Frame frame)
        {
            try
            {
                var matches = await _bitmap.Dispatcher.InvokeAsync(() => CheckFrame(frame));
                if (matches)
                {
                    await Task.Run(() => FillPixelsFromFrameData(frame.Data)).ConfigureAwait(false);
                    await _bitmap.Dispatcher.InvokeAsync(UpdateBitmap);
                }
            }
            finally
            {
                OnProcessingFinished(frame);
            }
        }

        private bool CheckFrame(Frame frame)
        {
            var formatMatches = frame.DataFormat == FrameDataFormat.Float;
            var sizeMatches = frame.Width == _bitmap.PixelWidth && frame.Height == _bitmap.PixelHeight;
            return formatMatches && sizeMatches;
        }

        private void UpdateBitmap()
        {
            var rect = new Int32Rect(0, 0, _bitmap.PixelWidth, _bitmap.PixelHeight);
            _bitmap.WritePixels(rect, _pixels, _bitmap.PixelWidth, 0);
        }

        private unsafe void FillPixelsFromFrameData(IntPtr data)
        {
            float* dataPtr = (float*)data.ToPointer();
            fixed (byte* pixelsStart = _pixels)
            {
                var pixelsEnd = pixelsStart + _pixels.Length;
                for (var pixelsPtr = pixelsStart; pixelsPtr < pixelsEnd; pixelsPtr++, dataPtr++)
                {
                    // From black to white each meter
                    *pixelsPtr = (byte)((*dataPtr) / 1000 * 255);
                }
            }
        }
    }
}
