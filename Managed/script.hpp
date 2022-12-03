#include <script.h>
#include "scene.hpp" 

#include <Vcclr.h>

namespace CLIEngine::Script
{
	ref class Script abstract
	{
	public:
		static bool LoadGCDLL(System::String^ path)
		{
			pin_ptr<const wchar_t> str = PtrToStringChars(path);
			return Engine::Script::LoadGCDLL((const wchar_t*)str);
		}

		static bool UnloadGCDLL()
		{
			return Engine::Script::UnloadGCDLL();
		}

		virtual void Begin() = 0;
		virtual void Update(float fElapsedTime) = 0;
	protected:
		GameObject^ _object;
	};


}