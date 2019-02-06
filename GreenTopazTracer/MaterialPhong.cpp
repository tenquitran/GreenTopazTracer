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
    // We are ignoring the distance between the light surface and the intersection point - hence, no attenuation.

    double dot = normal.dot(lightVector);

    if (dot > 0.0)
    {
        return (m_diffuseColor * lightColor * lightBrightness * dot).clamp();
    }

    return Color();
}

Color MaterialPhong::calcSpecularColor(const Vector3& normal, const Vector3& lightVector, 
	const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const
{
	if (m_specularity <= 0.0)
	{
		return Color();
	}

    Vector3 lightVector2 = -lightVector;

	Vector3 reflectedRaySpec = (2 * lightVector2.dot(normal) * normal - lightVector2).normalize();

	double dot = rayDirection.dot(reflectedRaySpec);

	if (dot > 0.0)
	{
		double specularCoefficient = pow(dot, m_specularity);

		// The material's specular color should be taken into account only for metal materials.
        return (lightColor * lightBrightness /** m_specularColor*/ * specularCoefficient).clamp();
		//return (lightColor * lightBrightness * m_specularColor * specularCoefficient).clamp();

        // TODO: temp
        //return Color(1.0, 0.0, 1.0) * lightBrightness * specularCoefficient;
	}

	return Color();
}

#if 0
Color MaterialPhong::calculatePhongColor( /*const Material& material,*/ const Vector3& intersection, 
    const Vector3& rayDirection, const Vector3& normal ) const
{
    Color ambient = m_ambientLight * m_ambientIntensity * material.m_ambientColor;

    Color diffuse;
    Color specular;

    double lightAttenuation = 1.0;

    for (const auto& itr : m_lights)
    {
        Intersectable const * const pIntersectable = dynamic_cast<Intersectable*>(itr.get());
        if (!pIntersectable)
        {
            assert(false); continue;
        }

#if 1
        // Distance from the light source to the surface in question.
        double distance = glm::length(pIntersectable->getCenter() - intersection);

        Sphere const * const pSphere = dynamic_cast<Sphere*>(itr.get());
        if (pSphere)
        {
            // A spherical light source emits light from the surface, not from the center.
            distance -= pSphere->getRadius();
        }

        assert(distance > 0.0);

        lightAttenuation = 1.0 / (1.0 + itr->m_attenuationFactor * glm::pow(distance, 2.0));
#endif

        Vector3 lightVector = glm::normalize(pIntersectable->getCenter() - intersection);

        // Calculate diffuse component.
        // Note: currently, we are ignoring the distance between the light surface and the intersection point - hence, no attenuation.
        if (material.isDiffuse())
        {
            double dot = glm::dot(normal, lightVector);
            if (dot > 0)
            {
                diffuse += material.m_diffuseColor * material.m_diffuseCoefficient * itr->m_color * itr->m_brightness * dot;
            }
        }

        // Calculate specular component.
        if (material.isSpecular())
        {
            Vector3 lightVector2 = -lightVector;
            Vector3 reflectedRaySpec = glm::normalize(2 * dot(lightVector2, normal) * normal - lightVector2);

            double dot = glm::dot(rayDirection, reflectedRaySpec);
            if (dot > 0.0)
            {
                double specularCoefficient = pow(dot, material.m_specularity);

                // The material's specular color should be taken into account only for metal materials.
                specular += itr->m_color /** material.m_specularColor*/ * itr->m_brightness * specularCoefficient;
            }
        }
    }

    //return (ambient + diffuse + specular.clamp());    // without light attenuation
    return (ambient + (diffuse.clamp() + specular.clamp()) * lightAttenuation);
}
#endif

#if 0
Color MaterialPhong::calculateColor(const HitInfo& hitInfo) const
{
	// TODO: stub
	return m_diffuseColor;
}
#endif
