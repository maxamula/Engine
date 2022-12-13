#include <script.h>
#include "scene.hpp" 

#include <Vcclr.h>
#include <vector>

namespace CLIEngine
{
	typedef std::vector<std::string>& (*fnScriptnames)(void);
	public ref class Script abstract
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

		static array<System::String^>^ GetScriptNames()
		{			
			std::vector<std::string>& scriptnames = Engine::Script::ScriptNames();
			int size = scriptnames.size();
			array<System::String^>^ ret = gcnew array<System::String^>(size);
			for (int i = 0; i < size; i++)
			{
				ret[i] = gcnew System::String(scriptnames[i].c_str());
			}
			return ret;
		}

		virtual void Begin() = 0;
		virtual void Update(float fElapsedTime) = 0;
	protected:
		GameObject^ _object;
	};


}