using libfreenect2Net;
using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

namespace Sample
{
    internal class JpegRenderer : SingleFrameConsumer
    {
        private readonly WriteableBitmap _bitmap;

        public JpegRenderer(FrameQueue queue, WriteableBitmap bitmap) 
            : base(queue, FrameType.Color)
        {
            _bitmap = bitmap;
        }

        protected override void StartProcessing(Frame frame)
        {
            if (frame.DataFormat != FrameDataFormat.Raw)
            {
                OnProcessingFinished(frame);
                return;
            }

            _bitmap.Dispatcher.BeginInvoke(new Action<Frame>(RenderFrame), frame);
        }

        private unsafe void RenderFrame(Frame frame)
        {
            using (var stream = new UnmanagedMemoryStream((byte*)frame.Data.ToPointer(), frame.DataSize))
            {
                var decoder = new JpegBitmapDecoder(stream, BitmapCreateOptions.None, BitmapCacheOption.Default);
                BitmapSource decodedImage = decoder.Frames[0];
                if (decodedImage.Format != _bitmap.Format)
                {
                    decodedImage = new FormatConvertedBitmap(decodedImage, _bitmap.Format, null, 0);
                }
                var rect = new Int32Rect(0, 0, decodedImage.PixelWidth, decodedImage.PixelHeight);
                _bitmap.Lock();
                decodedImage.CopyPixels(rect, _bitmap.BackBuffer, _bitmap.BackBufferStride * _bitmap.PixelHeight, _bitmap.BackBufferStride);
                _bitmap.AddDirtyRect(rect);
                _bitmap.Unlock();
            }

            OnProcessingFinished(frame);
        }
    }
}
