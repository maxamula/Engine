#pragma once
#include "API/window.h"
#include <window.h>

namespace Engine
{
	Window& MakeWindow(HINSTANCE hInst, GFX_WND_DESC& desc);
	void DestroyWindow(Window& wnd);
}