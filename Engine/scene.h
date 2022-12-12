#pragma once
#include "API/scene.h"
#include <entt/entt.hpp>


namespace Engine
{
	class CScene;

	ENGINE_API class CGameObject : public GameObject
	{
		friend class CScene;
	public:
		CGameObject() = default;
		void AddScriptComponent(Script::ScriptCreator creator) override;
		Script::c_Script& GetScriptComponent() override;
		void RemoveScriptComponent() override;
		GameObject& AddChild() override;
		void RemoveChild(GameObject& object) override;
		bool operator==(GameObject& other) override;
		bool operator==(const CGameObject other);
	private:
		CScene* m_pScene = NULL;
		entt::entity m_handle{0};
		std::vector<CGameObject> m_objects;
	};

	ENGINE_API class CScene : public Scene
	{
		friend class CGameObject;
	public:
		CScene() = default;
		GameObject& AddChild() override;
		void RemoveChild(GameObject& object) override;
		
	private:
		template <class T>
		constexpr void _AddComponent(entt::entity objId, T& component) { m_reg.emplace_or_replace<T>(objId, component); }
		template <class T>
		constexpr void _AddComponent(entt::entity objId, T&& component) { m_reg.emplace_or_replace<T>(objId, component); }
		template <class T>
		constexpr void _RemoveComponent(entt::entity objId) { m_reg.remove<T>(objId); }
		template <class T>
		T& _GetComponent(entt::entity objId) { return m_reg.get<T>(objId); }
		template <class T>
		constexpr bool _HasComponent(entt::entity objId) { return m_reg.try_get<T>(objId) ? true : false; }

		entt::registry m_reg{};
		std::vector<CGameObject> m_objects;
	};
}