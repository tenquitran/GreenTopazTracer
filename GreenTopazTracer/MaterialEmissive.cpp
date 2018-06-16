#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


MaterialEmissive::MaterialEmissive(const Color& emissive, double intensity)
	: m_emissive(emissive), m_intensity(intensity)
{
}

MaterialEmissive::~MaterialEmissive()
{
}

Color MaterialEmissive::calculateColor(const HitInfo& hitInfo) const
{
	return (m_emissive * m_intensity);
}
