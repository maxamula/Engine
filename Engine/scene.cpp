#include "scene.h"

namespace Engine
{
	Scene& CreateScene()
	{
		return *new CScene();
	}
}