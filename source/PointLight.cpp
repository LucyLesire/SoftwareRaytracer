#include "PointLight.h"



Elite::PointLight::PointLight(Elite::FPoint3 pos, RGBColor color, float intensity)
{
	m_Pos = pos;
	m_Color = color;
	m_Intensity = intensity;
	m_OldIntensity = intensity;
}

Elite::PointLight::~PointLight()
{
}

Elite::FVector3 Elite::PointLight::GetDirection(const Elite::FPoint3& posToShade) const
{
	return (Elite::FVector3{ m_Pos - posToShade });
}

Elite::RGBColor Elite::PointLight::GetRadiance(const Elite::FPoint3& posToShade)
{
	RGBColor radiance{};

	auto radius = m_Pos - posToShade;

	radiance = m_Color * m_Intensity / Elite::SqrMagnitude(radius);

	return radiance;
}

void Elite::PointLight::TurnOffLight()
{
	if (m_Intensity == 0.f)
	{
		m_Intensity = m_OldIntensity;
	}
	else
	{
		m_Intensity = 0.f;
	}
}
