#include <window.h>

namespace CLIEngine
{
	public ref struct GFX_WND_DESC
	{
	public:
		System::IntPtr callback;
		System::IntPtr hParent{};
		System::String^ caption = L"Game";
		unsigned short left = 0;
		unsigned short top = 0;
		unsigned short width = 1280;
		unsigned short height = 720;

	};

	public ref class Window
	{
	internal:
		Engine::Window* _impl;
	public:
		Window(Engine::Window* impl) : _impl(impl) {};
		void Destroy() { _impl->Destroy(); }

		void ShowWnd() { _impl->ShowWnd(); }
		void CloseWnd() { _impl->CloseWnd(); }
		void SetWindowSize(unsigned short width, unsigned short height) { _impl->SetWindowSize(width, height); }
		void SetWindowCaption(const wchar_t* szCaption) { _impl->SetWindowCaption(szCaption); }

		bool IsFullscreen() { return _impl->IsFullscreen(); }
		bool IsClosed() { return _impl->IsClosed(); }
		unsigned short Width() { return _impl->Width(); }
		unsigned short Height() { return _impl->Height(); }
		System::IntPtr WinId() { return System::IntPtr(_impl->WinId()); }
	};
}