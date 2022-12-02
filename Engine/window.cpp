#include "window.h"
#include <core.h>
namespace Engine
{
	Window& MakeWindow(HINSTANCE hInst, GFX_WND_DESC& desc)
	{
		return *new Renderer::Window(hInst, desc);
	}
}