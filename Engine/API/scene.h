#pragma once
#include "common.h"
#include "script.h"

namespace Engine
{
	ENGINE_API class GameObject
	{
	public:
		virtual void AddScriptComponent(Script::ScriptCreator creator) = 0;
		virtual Script::c_Script& GetScriptComponent() = 0;
		virtual void RemoveScriptComponent() = 0;
	};

	ENGINE_API class Scene
	{
	public:
		virtual GameObject& CreateObject() = 0;
		virtual void RemoveObject(GameObject& object) = 0;
	};

	ENGINE_API Scene& CreateScene();
}