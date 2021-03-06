﻿using libfreenect2Net;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Sample
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private WriteableBitmap _colorBitmap;
        private WriteableBitmap _depthBitmap;
        private Context _context;
        private Device _device;
        private FrameQueue _frameQueueSource;
        private FrameQueue _frameQueueRegistered;
        private readonly List<FrameConsumer> _frameConsumers = new List<FrameConsumer>();
        private Registration _registration;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _context = new Context();

            var deviceCount = _context.EnumerateDevices();
            LogMessage("Found {0} device(s)", deviceCount);

            var defaultSerial = _context.GetDefaultDeviceSerialNumber();
            LogMessage("Default serial: {0}", defaultSerial);

            _colorBitmap = new WriteableBitmap(Context.DepthFrameWidth, Context.DepthFrameHeight, 96, 96, PixelFormats.Bgr32, null);
            ColorImage.Source = _colorBitmap;

            _depthBitmap = new WriteableBitmap(Context.DepthFrameWidth, Context.DepthFrameHeight, 96, 96, PixelFormats.Gray8, null);
            DepthImage.Source = _depthBitmap;
        }

        protected override void OnClosed(EventArgs e)
        {
            _context?.Dispose();

            base.OnClosed(e);
        }

        private void LogMessage(string messageOrFormat, params object[] args)
        {
            Log.AppendText(
                $"[{DateTime.Now.ToString("HH':'mm':'ss.fff")}]" + 
                string.Format(messageOrFormat, args) + 
                Environment.NewLine);
        }



        private void Start_Click(object sender, RoutedEventArgs e)
        {
            if (_device != null)
            {
                LogMessage("Already started");
                return;
            }

            try
            {
                _device = _context.OpenDefaultDevice();
            }
            catch (NotSupportedException ex)
            {
                LogMessage(ex.Message);
            }
            if (_device == null)
            {
                LogMessage("Could not open default device");
                return;
            }

            Start.IsEnabled = false;
            Stop.IsEnabled = true;

            _frameQueueSource = new FrameQueue();
            _frameQueueRegistered = new FrameQueue();
            _frameConsumers.Add(new DummyFrameConsumer(_frameQueueSource, FrameType.InfraRed));
            _frameConsumers.Add(new ColorRenderer(_frameQueueRegistered, _colorBitmap));
            _frameConsumers.Add(new DepthRenderer(_frameQueueRegistered, _depthBitmap));

            var listener = new FrameListener(_frameQueueSource, message => Dispatcher.BeginInvoke(new Action(() => LogMessage(message))));
            _device.SetColorListener(listener);
            _device.SetDepthListener(listener);

            _device.StartAll();
            LogMessage("Started");

            // Device parameters can only be obtained after start
            _registration = new Registration(_device.InfraRedCameraParameters, _device.ColorCameraParameters);
            var firmwareVersion = _device.FirmwareVersion;
            LogMessage("Device firmware: {0}", firmwareVersion);

            _frameConsumers.Add(new FrameRegistrationProcessor(_frameQueueSource, _frameQueueRegistered, _registration));
            _frameConsumers.ForEach(fc => fc.Start());
        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            if (_device == null)
            {
                LogMessage("Not started yet");
                return;
            }

            _device.Stop();
            LogMessage("Stopped");

            _device.Dispose();
            _device = null;

            _frameConsumers.ForEach(fc => fc.Stop());
            _frameConsumers.Clear();
            _frameQueueSource.Dispose();
            _frameQueueRegistered.Dispose();
            _registration.Dispose();

            Start.IsEnabled = true;
            Stop.IsEnabled = false;
        }
    }
}
