using Editor.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Editor.LevelEditor
{
    /// <summary>
    /// Логика взаимодействия для Viewport.xaml
    /// </summary>
    public partial class Viewport : UserControl, IDisposable
    {
        public Viewport()
        {
            InitializeComponent();
            Loaded += OnRenderSurfaceLoaded;
        }

        private void OnRenderSurfaceLoaded(object sender, RoutedEventArgs e)
        {
            Loaded -= OnRenderSurfaceLoaded;
            _host = new RSHost((ushort)ActualWidth, (ushort)ActualHeight);
            _host.MessageHook += new HwndSourceHook(HostWndProc);
            Content = _host;
            var window = Window.GetWindow(this);

            var helper = new WindowInteropHelper(window);
            HwndSource.FromHwnd(helper.Handle)?.AddHook(MainWndProc);
        }

        private IntPtr MainWndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                case 0x0214:    // WM_SIZING
                    _canResize = false;
                    _moved = false;
                    break;
                case 0x0231:    // WM_ENTERSIZEMOVE
                    _moved = true;
                    break;
                case 0x0232:    // WM_EXITSIZEMOVE
                    _canResize = true;
                    if (!_moved)
                        _host.Window.SetWindowSize(0, 0);
                    break;
            }
            return IntPtr.Zero;
        }

        private bool _canResize = true;
        private bool _moved = false;
        private IntPtr HostWndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                case 0x0214:    // WM_SIZING
                    break;
                case 0x0231:    // WM_ENTERSIZEMOVE
                    break;
                case 0x0232:    // WM_EXITSIZEMOVE
                    break;
                case 0x0005:    // WM_SIZE
                    if (_canResize)
                        _host.Window.SetWindowSize(0, 0);
                    break;
            }
            return IntPtr.Zero;
        }

        public void Dispose()
        {
            _host.Dispose();
        }

        private RSHost _host = null;
    }
}
