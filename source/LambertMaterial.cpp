#include "LambertMaterial.h"
#include "EBRDF.h"

Elite::LambertMaterial::LambertMaterial(float reflectance, RGBColor color)
{
	m_DiffuseReflectance = reflectance;
	m_DiffuseColor = color;
}

Elite::RGBColor Elite::LambertMaterial::Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const
{
	return (BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance));
}