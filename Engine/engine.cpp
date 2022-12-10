#include "API/engine.h"
#include "script.h"
#include <core.h>

#include <thread>

using namespace Engine;

#define ENGINE_ENTRY(reason) if(Engine::Script::pInitializer) Engine::Script::pInitializer(hInst, reason)
#define LAUNCH_GFX bRunGFX = true; gfxThread = std::thread(GFXThread);
#define LAUNCH_LOGIC bRunLogic = true; logicThread = std::thread(LogicThread);
#define EXIT_GFX bRunGFX = false; if(gfxThread.joinable()) gfxThread.join();
#define EXIT_LOGIC bRunLogic = false; if(logicThread.joinable()) logicThread.join();

typedef void(*IMGUICB)(void);

void GFXThread();
void LogicThread(int a);

namespace Engine
{
	bool bRunGFX = false;
	bool bRunLogic = false;
	bool bInitialized = false;
	std::thread gfxThread;
	std::thread logicThread;

	// Imgui stuff
	IMGUICB imguicb = NULL;
	bool bImguiInitialized = false;
	Renderer::D3DDescriptorHeap imguiSRV;

	void Initialize()
	{
		Renderer::Initialize();
		bInitialized = true;
	}

	void Shutdown()
	{
		bInitialized = false;
		Renderer::Shutdown();		
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		Renderer::Window* This = (Renderer::Window*)GetWindowLongPtr(hwnd, 0);
		switch (msg)
		{
		case WM_DESTROY:
			This->m_surface.Release();
			delete This;
			return DefWindowProc(hwnd, msg, wparam, lparam);
			break;
		case WM_NCDESTROY:
			return DefWindowProc(hwnd, msg, wparam, lparam);
			break;
		case WM_EXITSIZEMOVE:
			GetClientRect(hwnd, &This->m_clientRect);
			break;
		case WM_SIZE:	// TODO resize surface
			if (wparam == SIZE_MAXIMIZED)
				GetClientRect(hwnd, &This->m_clientRect);
			break;
		case WM_SYSCOMMAND:
			if (wparam == SC_RESTORE)
				GetClientRect(hwnd, &This->m_clientRect);
			break;
		case WM_QUIT:
			This->Destroy();
			break;
		}
		return (This && This->m_callback) ? This->m_callback(This, hwnd, msg, wparam, lparam) : DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	ENGINE_ENTRY(REASON_INITIALIZE);
	if (Engine::bInitialized)
	{
		//LAUNCH_GFX;
		//LAUNCH_LOGIC;
		MSG msg;
		while (GetMessage(&msg, NULL, NULL, NULL))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//EXIT_LOGIC;
		//EXIT_GFX;
	}
	ENGINE_ENTRY(REASON_SHUTDOWN);
	return 0;
}

void GFXThread()
{
	while (bRunGFX)
	{
		
	}
}

void LogicThread(int a)
{
	while(bRunLogic)
	{

	}
}