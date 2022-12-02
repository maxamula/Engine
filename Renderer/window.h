#pragma once
#include "common.h"
#include "core.h"
#include "d3dsurface.h"
#include <window.h>		// Interface
#include <common.h>
#include <windows.h>

#define WND_CLASS L"EngineWindow"

namespace Renderer
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	ENGINE_API class Window : public Engine::Window
	{
		friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:
		Window() = delete;
		Window(HINSTANCE hInst, Engine::GFX_WND_DESC& desc);
		static void Initialize();
		inline static void Terminate() { UnregisterClass(WND_CLASS, GetModuleHandle(NULL)); }

		inline void Destroy() override { ::DestroyWindow(m_hWnd); }

		void ShowWnd() override;
		void CloseWnd() override;
		void SetWindowSize(uint16_t width, uint16_t height) override;
		void SetWindowCaption(const wchar_t* szCaption) override;

		inline bool IsFullscreen() const override { return m_bFullscreen; }
		inline bool IsClosed() const override { return m_bClosed; }
		inline uint16_t Width() const override { return m_width; }
		inline uint16_t Height() const override { return m_height; }
		inline HWND WinId() const override { return m_hWnd; }

	private:
		D3DSurface m_surface{};

		HWND m_hWnd = NULL;
		HWND m_parent = NULL;
		HINSTANCE m_hInst = NULL;
		WndProcFnPtr m_callback = NULL;
		uint16_t m_width = 1280;
		uint16_t m_height = 720;
		std::wstring m_caption = L"Game";
		RECT m_wndRect{};
		RECT m_clientRect{};
		DWORD m_dwStyle = WS_OVERLAPPED | WS_SYSMENU;
		bool m_bFullscreen = false;
		bool m_bClosed = true;
	};
}


