#pragma once
#include <vector>
#include "Singleton.h"
#include "BaseMaterial.h"

namespace Elite
{
	class MaterialManager : public Singleton<MaterialManager>
	{
	public:
		MaterialManager();
		~MaterialManager();

		void AddMaterial(BaseMaterial* mat);
		std::vector<BaseMaterial*> GetMaterial() const;
		BaseMaterial* GetLatestMaterial() const;

	private:
		std::vector<BaseMaterial*> m_pMaterials;

		friend class Singleton<MaterialManager>;
	};
}

