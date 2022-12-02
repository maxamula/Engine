#pragma once
#include "common.h"

namespace Engine
{
	ENGINE_API class GameObject
	{
	public:
	};

	ENGINE_API class Scene
	{
	public:
		virtual GameObject& CreateObject() = 0;
		virtual void RemoveObject(GameObject& object) = 0;
	};

	ENGINE_API Scene& CreateScene();
}