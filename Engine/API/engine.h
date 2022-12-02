#pragma once
#include "scene.h"
#include "window.h"

#define ENGINE_INITIALIZER

namespace Engine
{
	ENGINE_API void Initialize();
	ENGINE_API void Shutdown();
}