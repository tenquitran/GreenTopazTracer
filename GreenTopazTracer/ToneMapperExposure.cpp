#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


ToneMapperExposure::ToneMapperExposure(ClrComponent exposure, ClrComponent gamma)
    : ToneMapper(EToneMapping::Exposure),
      m_exposure(exposure), m_gamma(gamma)
{
}

Color ToneMapperExposure::convert(const Color& clr) const
{
    // Tone mapping.
    Color mapped = Color(1.0) - Color(exp(-clr.m_red * m_exposure), exp(-clr.m_green * m_exposure), exp(-clr.m_blue * m_exposure));

    // Gamma correction.
    return mapped.raiseToPower(Vector3(1.0 / m_gamma));
}

