#pragma once
#include "common.h"

namespace Engine { class Window; }
typedef LRESULT(__stdcall* WndProcFnPtr)(Engine::Window* This, HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace Engine
{

	ENGINE_API struct GFX_WND_DESC
	{
		WndProcFnPtr callback = NULL;
		HWND hParent = NULL;
		wchar_t* szCaption = (wchar_t*)L"Game";
		uint16_t left = 0;
		uint16_t top = 0;
		uint16_t width = 1280;
		uint16_t height = 720;
	};

	ENGINE_API class Window
	{
	public:
		virtual void Destroy() = 0;
		virtual void ShowWnd() = 0;
		virtual void CloseWnd() = 0;
		virtual void SetWindowSize(uint32_t width, uint32_t height) = 0;
		virtual void SetWindowCaption(const wchar_t* szCaption) = 0;

		virtual bool IsFullscreen(uint8_t id) const = 0;
		virtual bool IsClosed(uint8_t id) const = 0;
		virtual uint16_t Width(uint8_t id) const = 0;
		virtual uint16_t Height(uint8_t id) const = 0;
		virtual HWND WinId(uint8_t id) const = 0;
	};

	ENGINE_API Window& MakeWindow(HINSTANCE hInst, GFX_WND_DESC& desc);
}