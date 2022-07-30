#include "SceneManager.h"
Elite::SceneManager::SceneManager()
{
}

Elite::SceneManager::~SceneManager()
{
	for (int i{}; i < m_pScenes.size(); i++)
	{
		delete m_pScenes[i];
		m_pScenes[i] = nullptr;
	}
	m_pScenes.clear();
}

void Elite::SceneManager::AddScene(Scene* scene)
{
	m_pScenes.push_back(scene);
}

const std::vector<Elite::Scene*> Elite::SceneManager::GetScene() const
{
	return m_pScenes;
}

void Elite::SceneManager::Update(float dT)
{
	for (auto s : m_pScenes)
	{
		s->Update(dT);
	}
}
