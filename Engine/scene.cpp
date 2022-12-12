#include "scene.h"

namespace Engine
{
	Scene& CreateScene()
	{
		return *new CScene();
	}

	void CGameObject::AddScriptComponent(Script::ScriptCreator creator)
	{
		m_pScene->m_reg.emplace_or_replace<Script::c_Script>(m_handle, creator(*this));
	}

	Script::c_Script& CGameObject::GetScriptComponent()
	{
		return m_pScene->_GetComponent<Script::c_Script>(m_handle);
	}

	void CGameObject::RemoveScriptComponent()
	{
		m_pScene->_RemoveComponent<Script::c_Script>(m_handle);
	}

	GameObject& CGameObject::AddChild()
	{
		CGameObject obj;
		obj.m_handle = m_pScene->m_reg.create();
		obj.m_pScene = m_pScene;
		return m_objects.emplace_back(obj);
	}

	void CGameObject::RemoveChild(GameObject& object)
	{
		CGameObject& cobject = reinterpret_cast<CGameObject&>(object);
		m_pScene->m_reg.destroy(cobject.m_handle);
		for (CGameObject& child : cobject.m_objects)
			cobject.RemoveChild(child);
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), cobject), m_objects.end());
	}
	
	bool CGameObject::operator==(GameObject& other)
	{
		if (m_handle == reinterpret_cast<CGameObject&>(other).m_handle)
			return true;
		return false;
	}

	bool CGameObject::operator==(const CGameObject other)
	{
		if (m_handle == other.m_handle)
			return true;
		return false;
	}

	GameObject& CScene::AddChild()
	{
		CGameObject obj;
		obj.m_handle = m_reg.create();
		obj.m_pScene = this;
		return m_objects.emplace_back(obj);
	}
	void CScene::RemoveChild(GameObject& object)
	{		
		CGameObject& cobject = reinterpret_cast<CGameObject&>(object);
		//assert(std::find(m_objects.begin(), m_objects.end(), cobject) != m_objects.end());
		m_reg.destroy(cobject.m_handle);
		for (CGameObject& child : cobject.m_objects)
			cobject.RemoveChild(child);
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), cobject), m_objects.end());
	}
}