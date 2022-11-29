#pragma once

namespace Engine
{
	class GameObject
	{
	public:
	};

	class Scene
	{
	public:
		virtual GameObject& CreateObject() = 0;
		virtual void RemoveObject(GameObject& object) = 0;
	};

	Scene& CreateScene();
}