#pragma once
#include "BaseMaterial.h"

namespace Elite
{
	class LambertMaterial : public BaseMaterial
	{
	public:
		LambertMaterial(float reflectance, RGBColor color);
		~LambertMaterial();
		 
		RGBColor Shade(const HitRecord& hitRecord, const FVector3& w0, const FVector3& w1) const override;
	};
}


