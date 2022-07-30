#include "DirectionalLight.h"

Elite::DirectionalLight::DirectionalLight(Elite::FVector3 direction, RGBColor color, float intensity)
{
	m_Direction = direction;
	m_Color = color;
	m_Intensity = intensity;
	m_OldIntensity = intensity;
}

Elite::DirectionalLight::~DirectionalLight()
{
}

Elite::FVector3 Elite::DirectionalLight::GetDirection(const Elite::FPoint3& posToShade) const
{
	return Elite::GetNormalized(m_Direction);
}

Elite::RGBColor Elite::DirectionalLight::GetRadiance(const Elite::FPoint3& posToShade)
{
	return m_Color * m_Intensity;
}

void Elite::DirectionalLight::TurnOffLight()
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