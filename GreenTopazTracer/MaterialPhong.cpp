#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


#if 0
MaterialPhong::MaterialPhong()
{
}
#endif

MaterialPhong::MaterialPhong(const Color& ambient, const Color& diffuse, const Color& specular, 
	double specularity, double reflectivity /*= 0.0*/, double opacity /*= 1.0*/, double refractionIndex /*= 1.0*/)
	: m_ambientColor(ambient), m_diffuseColor(diffuse), m_specularColor(specular), m_specularity(specularity), 
	  m_reflectivity(reflectivity), m_opacity(opacity), m_refractionIndex(refractionIndex)
{
}

MaterialPhong::~MaterialPhong()
{
}

Color MaterialPhong::calcAmbientColor(ClrComponentType ambIntensity) const
{
	return (ambIntensity * m_ambientColor);
}

Color MaterialPhong::calcDiffuseColor(const Vector3& normal, const Vector3& lightVector, const Color& lightColor, double lightBrightness) const
{
	if (m_diffuseColor.isBlack())
	{
		return m_diffuseColor;
	}

	// We are ignoring the distance between the light surface and the intersection point - hence, no attenuation.
	double dot = normal.dot(lightVector);

	if (dot > 0.0)
	{
		return (m_diffuseColor * lightColor * lightBrightness * dot);
	}
	
	return Color();
}

Color MaterialPhong::calcSpecularColor(const Vector3& normal, const Vector3& lightVector, 
	const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const
{
	if (m_specularColor.isBlack())
	{
		return m_specularColor;
	}

	Vector3 lightVector2 = -lightVector;

	Vector3 reflectedRaySpec = (2 * lightVector2.dot(normal) * normal - lightVector2).normalize();

	double dot = rayDirection.dot(reflectedRaySpec);
	if (dot > 0.0)
	{
		double specularCoefficient = pow(dot, m_specularity);

		// The material's specular color should be taken into account only for metal materials.
		return (lightColor * m_specularColor * lightBrightness * specularCoefficient);
	}

	return Color();
}

#if 0
Color MaterialPhong::calculateColor(const HitInfo& hitInfo) const
{
	// TODO: stub
	return m_diffuseColor;
}
#endif
