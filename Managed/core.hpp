#include "scene.hpp"
#include "window.hpp"

namespace CLIEngine
{
	public ref class Core
	{
	public:
		static Scene^ CreateScene() { return gcnew Scene(&Engine::CreateScene()); }
		static Window^ MakeWindow(GFX_WND_DESC^ desc) { return gcnew Window(&Engine::MakeWindow(GetModuleHandle(NULL), (Engine::GFX_WND_DESC&)desc));}
	};
}