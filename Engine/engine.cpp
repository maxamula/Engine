#include "API/engine.h"
#include <core.h>

namespace Engine
{
	void Initialize()
	{
		Renderer::Initialize();
	}

	void Shutdown()
	{
		Renderer::Shutdown();
	}
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	
	return 0;
}