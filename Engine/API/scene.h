#pragma once
#include "common.h"
#include "script.h"

namespace Engine
{
	class GameObject;

	ENGINE_API class GameObjectParent
	{
	public:
		virtual GameObject& AddChild() = 0;
		virtual void RemoveChild(GameObject& object) = 0;
	};

	ENGINE_API class GameObject : public GameObjectParent
	{
	public:
		virtual void AddScriptComponent(Script::ScriptCreator creator) = 0;
		virtual Script::c_Script& GetScriptComponent() = 0;
		virtual void RemoveScriptComponent() = 0;
		virtual bool operator==(GameObject& other) = 0;
	};

	ENGINE_API class Scene : public GameObjectParent
	{
	public:

	};

	ENGINE_API Scene& CreateScene();
}