#pragma once
#include "common.h"
//#include "scene.h"
#include <memory>
#include <assert.h>

namespace Engine
{
	class GameObject;
	namespace Script
	{
	
		class Script
		{
		public:
			Script() = delete;
			virtual void __fastcall Begin() = 0;
			virtual void __fastcall Update(float fElapsedTime) = 0;
		protected:
			explicit Script(GameObject& obj)
				: m_object(obj)
			{}
			GameObject& m_object;
		};

		using ScriptPtr = std::unique_ptr<Script>;								// Pointer to script instance
		using ScriptCreator = ScriptPtr(*)(GameObject& object);					// Pointer to CreateScript inst

		template <class Script_Impl>
		ScriptPtr CreateScript(GameObject& obj)
		{
			return std::make_unique<Script_Impl>(obj);
		}

		struct c_Script
		{
		public:
			ScriptPtr pScriptInst;
		};

		ENGINE_API bool LoadGCDLL(const wchar_t* path);
		ENGINE_API bool UnloadGCDLL();
		ENGINE_API uint8_t RegisterScript(uint64_t handle, ScriptCreator creator);
		ENGINE_API uint8_t RegisterScriptName(const char* name);
		ENGINE_API uint8_t SetInitializer(void* pFunc);
	}
}