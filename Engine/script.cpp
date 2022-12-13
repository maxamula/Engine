#include "script.h"

namespace Engine::Script
{
	HMODULE hGCDll;

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
	// Hidden

	//ScriptCreator byname(const char* name)
	//{
	//	auto creator = ScriptCreators().find(std::hash<std::string>()(name));
	//	assert(creator != ScriptCreators().end() && creator->first == std::hash<std::string>()(name));
	//	return creator->second;
	//}
}