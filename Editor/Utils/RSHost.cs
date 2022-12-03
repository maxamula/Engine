using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;

namespace Editor.Utils
{
    class RSHost : HwndHost
    {
        public RSHost(ushort width, ushort height)
        {
            _width = width;
            _height = height;
        }
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            try
            {
                CLIEngine.GFX_WND_DESC desc = new CLIEngine.GFX_WND_DESC();
                desc.hParent = hwndParent.Handle;
                desc.caption = "VIEWPORT";
                desc.width = _width;
                desc.height = _height;
                Window = CLIEngine.Core.MakeWindow(desc);
                _hWnd = Window.WinId();
                return new HandleRef(this, _hWnd);
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                this.Dispose();
                return new HandleRef(this, IntPtr.MaxValue);
            }
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            Window.Destroy();
        }

        public void Resize()
        {

        }

        public CLIEngine.Window Window { get; private set; }
        private readonly ushort _width = 800;
        private readonly ushort _height = 600;
        private IntPtr _hWnd = IntPtr.Zero;
    }
}
