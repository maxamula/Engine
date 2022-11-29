#pragma once
#include "common.h"
#include <windows.h>

#define WND_CLASS L"EngineWindow"

typedef LRESULT(__stdcall* WndProcFnPtr)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace Renderer
{
	struct GFX_WND_DESC
	{
		WndProcFnPtr callback = NULL;
		HWND hParent = NULL;
		wchar_t* szCaption = (wchar_t*)L"Game";
		uint32_t left = 0;
		uint32_t top = 0;
		uint32_t width = 1280;
		uint32_t height = 720;
	};

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	class Window
	{
		friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:
		Window() = delete;
		Window(HINSTANCE hInst, GFX_WND_DESC& desc);
		static void s_ctor(void);

	private:
		HWND m_hWnd = NULL;
		HWND m_parent = NULL;
		HINSTANCE m_hInst = NULL;
		WndProcFnPtr m_callback = NULL;
		uint32_t m_width = 1280;
		uint32_t m_height = 720;
		std::wstring m_caption = L"Game";
		RECT m_wndRect{};
		RECT m_clientRect{};
		DWORD m_dwStyle = WS_OVERLAPPED | WS_SYSMENU;
		bool m_bFullscreen = false;
		bool m_bClosed = true;
	};
}


