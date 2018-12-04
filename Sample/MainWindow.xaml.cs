using libfreenect2Net;
using System;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows;

namespace Sample
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Context _context;
        private Device _device;

        public MainWindow()
        {
            InitializeComponent();
        }

        private async void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _context = new Context();

            var deviceCount = _context.EnumerateDevices();
            LogMessage("Found {0} device(s)", deviceCount);

            var defaultSerial = _context.GetDefaultDeviceSerialNumber();
            LogMessage("Default serial: {0}", defaultSerial);
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

            _device = _context.OpenDefaultDevice();
            if (_device == null)
            {
                LogMessage("Could not open default device");
                return;
            }

            Start.IsEnabled = false;
            Stop.IsEnabled = true;

            var listener = new FrameListener(message => Dispatcher.BeginInvoke(new Action(() => LogMessage(message))));
            _device.SetColorListener(listener);
            _device.SetDepthListener(listener);

            _device.StartAll();
            LogMessage("Started");

            var firmwareVersion = _device.FirmwareVersion;
            LogMessage("Device firmware: {0}", firmwareVersion);
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

            Start.IsEnabled = true;
            Stop.IsEnabled = false;
        }
    }
}
