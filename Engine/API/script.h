#pragma once
#include "common.h"
#include "scene.h"
#include <memory>

namespace Engine::Script
{
	class Script
	{
	public:
		virtual ~Script() = default;
		virtual void __fastcall Begin() = 0;
		virtual void __fastcall Update(float fElapsedTime) = 0;
	protected:
		GameObject& m_object;
	};
	using ScriptPtr = std::unique_ptr<Script>;								// Pointer to script instance
	using ScriptCreator = ScriptPtr(*)(void* pScene, uint32_t objHandle);	// Pointer to CreateScript inst

	ENGINE_API bool LoadGCDLL(const wchar_t* path);
	ENGINE_API bool UnloadGCDLL();
	ENGINE_API uint8_t RegisterScript(uint64_t handle, ScriptCreator creator);
	ENGINE_API uint8_t RegisterScriptName(const char* name);
}