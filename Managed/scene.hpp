#include <scene.h>

namespace CLIEngine
{

	public ref class GameObject
	{
	internal:
		Engine::GameObject* _impl;
	public:
		GameObject(Engine::GameObject* impl) : _impl(impl) {};
		GameObject^ AddChild()
		{
			return gcnew GameObject(&_impl->AddChild());
		}
		void RemoveChild(GameObject^ object)
		{
			_impl->RemoveChild(*object->_impl);
		}
	};


	public ref class Scene
	{
	internal:
		Engine::Scene* _impl;		
	public:
		Scene(Engine::Scene* impl) : _impl(impl) {};
		GameObject^ AddChild()
		{
			return gcnew GameObject(&_impl->AddChild());
		}

		void RemoveChild(GameObject^ object)
		{
			_impl->RemoveChild(*object->_impl);
		}
	};
}