#include "PBRMaterial.h"
#include "EBRDF.h"

Elite::PBRMaterial::PBRMaterial(Elite::RGBColor diffuseColour,float diffuseReflectance, float roughness, bool metal, const Elite::RGBColor& reflectivity)
{
	m_Roughness = roughness;
	m_AlbedoColour = reflectivity;
	m_Metal = metal;
	m_DiffuseColor = diffuseColour;
	m_DiffuseReflectance = diffuseReflectance;
}

Elite::RGBColor Elite::PBRMaterial::Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const
{
	Elite::RGBColor F0 = m_AlbedoColour;
	Elite::FVector3 halfVector = (w0 + w1) / Magnitude(w0 + w1);
	Elite::RGBColor fresnel = BRDF::Fresnel(halfVector, w1, F0);
	float normalD = BRDF::NormalD(hitRecord.m_Normal, halfVector, m_Roughness * m_Roughness);
	float geometry = BRDF::Geometry(hitRecord.m_Normal, w1, m_Roughness * m_Roughness) * BRDF::Geometry(hitRecord.m_Normal, w0, m_Roughness * m_Roughness);
	Elite::RGBColor specular = ((fresnel * normalD * geometry) / (4 * Elite::Dot(w1, hitRecord.m_Normal) * Elite::Dot(w0, hitRecord.m_Normal)));
	
	Elite::RGBColor kd = (Elite::RGBColor{ 1.f, 1.f, 1.f } - fresnel);
	if (m_Metal)
	{
		kd = { 0.f,0.f,0.f };
	}

	Elite::RGBColor diffuse = (BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance) * kd);

	return diffuse + specular;
}
