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