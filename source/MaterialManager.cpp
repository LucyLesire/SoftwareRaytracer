#include "MaterialManager.h"

Elite::MaterialManager::MaterialManager()
{
}

Elite::MaterialManager::~MaterialManager()
{
	for (int i{}; i < m_pMaterials.size(); i++)
	{
		delete m_pMaterials[i];
		m_pMaterials[i] = nullptr;
	}
	m_pMaterials.clear();
}

void Elite::MaterialManager::AddMaterial(BaseMaterial* mat)
{
	m_pMaterials.push_back(mat);
}

std::vector<Elite::BaseMaterial*> Elite::MaterialManager::GetMaterial() const
{
	return m_pMaterials;
}

Elite::BaseMaterial* Elite::MaterialManager::GetLatestMaterial() const
{
	return m_pMaterials.back();
}

