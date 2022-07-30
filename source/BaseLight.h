#pragma once
#include "EMath.h"
#include "ERGBColor.h"

namespace Elite
{
	class BaseLight
	{
	public:
		BaseLight();
		~BaseLight();

		virtual Elite::FVector3 GetDirection(const Elite::FPoint3& posToShade) const = 0;
		virtual Elite::RGBColor GetRadiance(const Elite::FPoint3& posToShade) = 0;
		virtual void TurnOffLight() = 0;
	protected:
		Elite::FVector3 m_Direction{};
		Elite::FPoint3 m_Pos{};
		Elite::RGBColor m_Color{};
		float m_Intensity{};
		float m_OldIntensity{};
	};
}


