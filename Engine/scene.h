#pragma once
#include "API/scene.h"
#include <entt/entt.hpp>

namespace Engine
{
	class CScene;

	class CGameObject : public GameObject
	{
		friend class CScene;
	public:

	private:
		CGameObject() = default;
		Scene* m_pScene = NULL;
		entt::entity m_handle{0};
	};

	class CScene : public Scene
	{
	public:
		CScene() = delete;
		inline GameObject& CreateObject() override
		{
			CGameObject obj;
			obj.m_handle = m_reg.create();
			obj.m_pScene = this;
			return obj;
		}
		inline void RemoveObject(GameObject& object) override
		{
			m_reg.destroy(reinterpret_cast<CGameObject&>(object).m_handle);
		}
	private:
		template <class T>
		void _AddComponent(entt::entity objId, T& component) { m_reg.emplace_or_replace<T>(objId, component); }
		template <class T>
		void _AddComponent(entt::entity objId, T&& component) { m_reg.emplace_or_replace<T>(objId, component); }
		template <class T>
		void _RemoveComponent(entt::entity objId) { m_reg.remove<T>(objId); }
		template <class T>
		T& _GetComponent(entt::entity objId) { return m_reg.get<T>(objId); }
		template <class T>
		bool _HasComponent(entt::entity objId) { return m_reg.try_get<T>(objId) ? true : false; }

		entt::registry m_reg{};
	};
}