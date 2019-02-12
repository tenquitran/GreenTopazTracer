#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


MaterialEmissive::MaterialEmissive(const Color& emissive, double intensity)
    : Material(EMaterialType::Emissive), 
      m_emissive(emissive), m_intensity(intensity)
{
}

MaterialEmissive::~MaterialEmissive()
{
}

Color MaterialEmissive::calcEmissiveColor() const
{
	return (m_emissive * m_intensity);
}
