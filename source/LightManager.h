#pragma once
#include <vector>
#include "Singleton.h"
#include "BaseLight.h"

namespace Elite
{
	class LightManager : public Singleton<LightManager>
	{
	public:
		LightManager();
		~LightManager();

		void AddLight(BaseLight* light);
		std::vector<BaseLight*> GetLights() const;

	private:
		std::vector<BaseLight*> m_pLights;

		friend class Singleton<LightManager>;
	};
}
