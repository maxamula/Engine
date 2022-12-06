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
}