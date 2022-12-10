#include "script.h"

namespace Engine::Script
{
	HMODULE hGCDll = NULL;
	fnEntry pInitializer = NULL;


	inline std::vector<std::string>& ScriptNames()
	{
		static std::vector<std::string> names;
		return names;
	}
	inline std::unordered_map<uint64_t, ScriptCreator>& ScriptCreators()	// guaranteed initialization
	{
		static std::unordered_map<uint64_t, ScriptCreator> reg;
		return reg;
	}

	bool LoadGCDLL(const wchar_t* path)
	{
		if (hGCDll)
			return false;
		hGCDll = LoadLibraryW(path);
		assert(hGCDll);
		return hGCDll ? true : false;
	}

	bool UnloadGCDLL()
	{
		if (!hGCDll)
			return false;
		ScriptNames().clear();
		ScriptCreators().clear();
		bool succseeded = FreeLibrary(hGCDll);
		if (succseeded)
			hGCDll = nullptr;
		return succseeded;
	}

	uint8_t RegisterScript(uint64_t handle, ScriptCreator creator)
	{
		return ScriptCreators().insert(std::unordered_map<uint64_t, ScriptCreator>::value_type{ handle, creator }).second;
	}
	uint8_t RegisterScriptName(const char* name)
	{
		ScriptNames().emplace_back(name);
		return true;
	}
	ScriptCreator GetScriptCreator(uint64_t handle)
	{
		auto creator = ScriptCreators().find(handle);
		assert(creator != ScriptCreators().end() && creator->first == handle);
		return creator->second;
	}
	uint8_t SetInitializer(void* pFunc)
	{
		pInitializer = (fnEntry)pFunc;
		return 0;
	}
	// Hidden
	/*ENGINE_API LPSAFEARRAY GetScriptNames()
	{
		if (ScriptNames().size() != 0)
		{
			CComSafeArray<BSTR> names(ScriptNames().size());
			for (uint32_t i = 0; i < ScriptNames().size(); i++)
			{
				names.SetAt(i, A2BSTR_EX(ScriptNames()[i].c_str()), false);
			}
			return names.Detach();
		}
		return NULL;
	}*/

	//ScriptCreator byname(const char* name)
	//{
	//	auto creator = ScriptCreators().find(std::hash<std::string>()(name));
	//	assert(creator != ScriptCreators().end() && creator->first == std::hash<std::string>()(name));
	//	return creator->second;
	//}
}