#pragma once
#include "API/script.h"
#include <vector>
#include <string>
#include <assert.h>
#include <unordered_map>

namespace Engine::Script
{
	typedef void(*fnEntry)(HINSTANCE hInst, DWORD dwReason);
	extern HMODULE hGCDll;
	extern fnEntry pInitializer;
	ScriptCreator GetScriptCreator(uint64_t handle);
}
