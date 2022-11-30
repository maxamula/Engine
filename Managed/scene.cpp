#include <scene.h>

namespace CLIEngine
{

	ref class GameObject
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