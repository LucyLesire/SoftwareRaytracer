#pragma once
#include "BaseLight.h"

namespace Elite
{
	class DirectionalLight : public BaseLight
	{
	public:
		DirectionalLight(Elite::FVector3 direction, RGBColor color, float intensity);
		~DirectionalLight();

		Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const override;

		Elite::RGBColor GetRadiance(const Elite::FPoint3& posToShadee) override;

		void TurnOffLight() override;
	};
}

