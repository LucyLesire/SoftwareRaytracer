#pragma once
#include "EMath.h"
#include "HitRecord.h"
namespace Elite
{
	class BaseMaterial
	{
	public:
		BaseMaterial();
		~BaseMaterial();

		virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const = 0;
	protected:
		float m_DiffuseReflectance{};
		RGBColor m_DiffuseColor{};
	};
}


