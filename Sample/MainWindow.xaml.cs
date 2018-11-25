using libfreenect2Net;
using System.Text;
using System.Windows;

namespace Sample
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var sb = new StringBuilder();
            using (var context = new Context())
            {
                var deviceCount = context.EnumerateDevices();
                sb.AppendFormat("Found {0} devices", deviceCount);
                sb.AppendLine();

                var defaultSerial = context.GetDefaultDeviceSerialNumber();
                sb.AppendFormat("Default serial: {0}", defaultSerial);
                sb.AppendLine();

                using (var defaultDevice = context.OpenDefaultDevice())
                {

                }
            }

            log.Text = sb.ToString();
        }
    }
}
