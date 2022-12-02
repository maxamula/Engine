#include <engine.h>
#include "scene.hpp"
#include "window.hpp"

#include <Vcclr.h>

namespace CLIEngine
{
	public ref class Core
	{
	public:
		static void Initialize() { Engine::Initialize(); }
		static void Shutdown() { Engine::Shutdown(); }
		static Scene^ CreateScene() { return gcnew Scene(&Engine::CreateScene()); }
		static Window^ MakeWindow(GFX_WND_DESC^ desc) 
		{
			Engine::GFX_WND_DESC _desc;
			_desc.callback = (WndProcFnPtr)desc->callback.ToPointer();
			_desc.hParent = (HWND)desc->hParent.ToPointer();
			pin_ptr<const wchar_t> str = PtrToStringChars(desc->caption);
			_desc.szCaption = (wchar_t*)str;
			_desc.top = desc->top;
			_desc.left = desc->left;
			_desc.width = desc->width;
			_desc.height = desc->height;
			return gcnew Window(&Engine::MakeWindow(GetModuleHandle(NULL), _desc));
		}
	};
}