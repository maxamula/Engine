#include <scene.h>

namespace CLIEngine
{

	public ref class GameObject
	{
	internal:
		Engine::GameObject* _impl;
	public:
		GameObject(Engine::GameObject* impl) : _impl(impl) {};
	};


	public ref class Scene
	{
	internal:
		Engine::Scene* _impl;		
	public:
		Scene(Engine::Scene* impl) : _impl(impl) {};
		static Scene^ CreateScene()
		{
			return gcnew Scene(&Engine::CreateScene());
		}


		GameObject^ CreateObject()
		{
			return gcnew GameObject(&_impl->CreateObject());
		}

		void RemoveObject(GameObject^ object)
		{
			_impl->RemoveObject(*object->_impl);
		}
	};
}