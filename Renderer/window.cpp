#include "window.h"

namespace Renderer
{
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
			
		}
		Window* This = (Window*)GetWindowLongPtr(hwnd, 0);
		return This->m_callback ? This->m_callback(hwnd, msg, wparam, lparam) : DefWindowProc(hwnd, msg, wparam, lparam);
	}

	Window::Window(HINSTANCE hInst, GFX_WND_DESC& desc)
		: m_hInst(hInst), m_parent(desc.hParent), m_callback(desc.callback), m_caption(desc.szCaption), m_width(desc.width), m_height(desc.height)
	{
		RECT rect{ desc.left, desc.top, desc.left + desc.width, desc.top + desc.height };
		m_dwStyle = desc.hParent != NULL ? WS_CHILD : WS_OVERLAPPEDWINDOW;
		AdjustWindowRect(&rect, m_dwStyle, FALSE);
		m_hWnd = CreateWindow(WND_CLASS, m_caption.c_str(), m_dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, m_parent, NULL, hInst, NULL);
		GetWindowRect(m_hWnd, &m_wndRect);
		GetClientRect(m_hWnd, &m_clientRect);
		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		// create rtv && swapchain
		new (&m_surface) D3DSurface(d3ddev, dxgiFactory, d3dcmd.CmdQueue(), &RTVHeap, m_hWnd, m_width, m_height);
	}
}