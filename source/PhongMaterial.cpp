#include "PhongMaterial.h"
#include "EBRDF.h"

Elite::PhongMaterial::PhongMaterial(RGBColor color, float specularReflectance, float phongExponent)
{
	m_PhongExponent = phongExponent;
	m_DiffuseColor = color;
	if (specularReflectance >= 1.0f)
	{
		m_SpecularReflectance = 0.99f;
		m_DiffuseReflectance = 0.01f;
	}
	else
	{
		m_SpecularReflectance = specularReflectance;
		m_DiffuseReflectance = 1.0f - specularReflectance;
	}
}

Elite::RGBColor Elite::PhongMaterial::Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const
{
	Elite::RGBColor color = BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance) + BRDF::Phong(m_DiffuseColor, m_SpecularReflectance, m_PhongExponent, w0, w1, hitRecord.m_Normal);
	return color;
}
