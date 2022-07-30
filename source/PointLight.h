#pragma once
#include "BaseLight.h"

namespace Elite
{
	class PointLight : public BaseLight
	{
	public:
		PointLight(Elite::FPoint3 pos, RGBColor color, float intensity);
		~PointLight();

		Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const override;

		Elite::RGBColor GetRadiance(const Elite::FPoint3& posToShade) override;

		void TurnOffLight() override;
	};
}



