#pragma once
#include <stdint.h>
#include <windows.h>
#include <string>


#ifdef _ENGINE
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#ifdef GCDLL
#define REGISTER_SCRIPT(TYPE) class TYPE; namespace { const uint8_t _reg##TYPE{Engine::Script::RegisterScript(std::hash<std::string>()(#TYPE), &Engine::Script::CreateScript<TYPE>)}; const uint8_t _name_##TYPE {Engine::Script::RegisterScriptName(#TYPE)};}
#else
#define REGISTER_SCRIPT(TYPE) class TYPE; namespace { const uint8_t _reg##TYPE{Engine::Script::RegisterScript(std::hash<std::string>()(#TYPE), &Engine::Script::CreateScript<TYPE>)};}
#endif