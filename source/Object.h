#pragma once
#include "Ray.h"
#include "HitRecord.h"
#include "BaseMaterial.h"

namespace Elite
{
	class Object
	{
	public:
		Object();
		virtual ~Object() = 0;

		virtual bool Hit(const Ray& ray, HitRecord& hitRecord) = 0;
		virtual void Update(float dT) = 0;

		virtual BaseMaterial* GetMaterial() = 0;
	protected:
	};
}



