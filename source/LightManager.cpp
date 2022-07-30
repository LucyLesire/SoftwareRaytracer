#include "LightManager.h"

Elite::LightManager::LightManager()
{
}

Elite::LightManager::~LightManager()
{
	for (int i{}; i < m_pLights.size(); i++)
	{
		delete m_pLights[i];
		m_pLights[i] = nullptr;
	}
	m_pLights.clear();
}

void Elite::LightManager::AddLight(BaseLight* scene)
{
	m_pLights.push_back(scene);
}

std::vector<Elite::BaseLight*> Elite::LightManager::GetLights() const
{
	return m_pLights;
}


