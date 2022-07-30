#pragma once
#include "EMath.h"
#include "ERGBColor.h"

struct HitRecord
{
	Elite::FPoint3 m_HitPoint{};
	Elite::FVector3 m_Normal{};
	Elite::RGBColor m_Colour{};
	float tValue{FLT_MAX};
	bool light{};
};