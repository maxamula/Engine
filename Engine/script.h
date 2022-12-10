#pragma once
#include "API/script.h"
#include <vector>
#include <string>
#include <assert.h>
#include <unordered_map>

namespace Engine::Script
{
	ScriptCreator GetScriptCreator(uint64_t handle);
}
