#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

#if 0
// If the ray intensity is lower than the threshold, the ray is considered insignificant.
const ClrComponentType Ray::IntensityThreshold = 0.001;
#endif

//////////////////////////////////////////////////////////////////////////


Ray::Ray()
	//: m_intensity{}
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction/*, const Color& intensity*/)
	: m_origin(origin), m_direction(direction)//, m_intensity(intensity)
{
}

// TODO: don't delete
#if 0
bool Ray::isIntensityTooLow() const
{
    return (   m_intensity.m_red   <= IntensityThreshold
            && m_intensity.m_green <= IntensityThreshold
            && m_intensity.m_blue  <= IntensityThreshold);
}
#endif
