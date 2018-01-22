#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

// If the ray intensity is lower than the threshold, the ray is considered insignificant.
const ClrComponentType Ray::INTENSITY_THRESHOLD = 0.001;

//////////////////////////////////////////////////////////////////////////


Ray::Ray()
	: m_intensity{}
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction, const Color& intensity)
	: m_origin(origin), m_direction(direction), m_intensity(intensity)
{
}

bool Ray::hasTooLowIntensity() const
{
	return (   m_intensity.m_red   <= INTENSITY_THRESHOLD
		    && m_intensity.m_green <= INTENSITY_THRESHOLD
		    && m_intensity.m_blue  <= INTENSITY_THRESHOLD);
}
