#pragma once

#include "EMath.h"

struct Ray
{
	Elite::FPoint3 m_Origin{};
	Elite::FVector3 m_Direction{};
	float m_TMin = 0.0001f;
	float m_TMax = FLT_MAX;
};

