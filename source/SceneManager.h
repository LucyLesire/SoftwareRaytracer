#pragma once
#include <vector>
#include "Scene.h"
#include "Singleton.h"

namespace Elite
{
	class SceneManager : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager();
		
		void AddScene(Scene* scene);
		const std::vector<Scene*> GetScene() const;

		void Update(float dT);
	private:

		std::vector<Scene*> m_pScenes;

		friend class Singleton<SceneManager>;
	};
}






