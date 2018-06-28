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

Color MaterialEmissive::calcAmbientColor(ClrComponentType ambIntensity) const 
{
	// For simplicity, suppose there is no ambient contribution.
	// Instead of this function, call calcEmissiveColor()
	
	UNREFERENCED_PARAMETER(ambIntensity);

	assert(false); return Color();
}

Color MaterialEmissive::calcDiffuseColor(const Vector3& normal, const Vector3& lightVector, const Color& lightColor, double lightBrightness) const 
{
	// For simplicity, suppose there is no diffuse contribution.
	// Instead of this function, call calcEmissiveColor()

	UNREFERENCED_PARAMETER(normal);
	UNREFERENCED_PARAMETER(lightVector);
	UNREFERENCED_PARAMETER(lightColor);
	UNREFERENCED_PARAMETER(lightBrightness);

	assert(false); return Color();
}

Color MaterialEmissive::calcSpecularColor(const Vector3& normal, const Vector3& lightVector, 
	const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const 
{
	// For simplicity, suppose there is no specular contribution.
	// Instead of this function, call calcEmissiveColor()

	UNREFERENCED_PARAMETER(normal);
	UNREFERENCED_PARAMETER(lightVector);
	UNREFERENCED_PARAMETER(lightColor);
	UNREFERENCED_PARAMETER(lightBrightness);
	UNREFERENCED_PARAMETER(rayDirection);

	assert(false); return Color();
}

Color MaterialEmissive::calcEmissiveColor() const
{
	return (m_emissive * m_intensity);
}

#if 0
Color MaterialEmissive::calculateColor(const HitInfo& hitInfo) const
{
	return (m_emissive * m_intensity);
}
#endif
