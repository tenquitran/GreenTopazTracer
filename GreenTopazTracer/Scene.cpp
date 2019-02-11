#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene(const Color& backgroundColor)
	: m_backgroundColor(backgroundColor)
{
    createPhongScene();
}

Scene::~Scene()
{
}

void Scene::createPhongScene()
{
    Color red(0.94, 0.28, 0.31);    // red (not too bright)

    // A sphere with the center at the top left corner.
    std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3(-400.0, -300.0, 0.0), 120.0, MaterialPhong(red, red, red, 1250 /*0.5*/));
    //sphere1->setColor(0.94, 0.28, 0.31);    // red (not too bright)

    //Color darkBlue(0.0, 0.0, 0.63);
    Color green(0.0, 1.0, 0.0);

    // A sphere with the center at the origin.
    std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3(), 150.0, MaterialPhong(/*darkBlue*/ green, green, green, 100.0));
    //std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3(), 85.0, MaterialPhong(/*darkBlue*/ green, green, green, 0.5));
    //sphere2->setColor(0.0, 0.0, 0.63);    // dark blue

    Color orange(1.0, 0.5, 0.15);

    std::unique_ptr<Sphere> sphere3 = std::make_unique<Sphere>(Vector3(180.0, 75.0, 50.0), 25.0, MaterialPhong(orange, orange, orange));
    //std::unique_ptr<Sphere> sphere3 = std::make_unique<Sphere>(Vector3(100.0, 55.0, 50.0), 15.0, MaterialPhong(orange, orange, orange, 0.5));

    m_objects.emplace_back(std::move(sphere1));
    m_objects.emplace_back(std::move(sphere2));
    m_objects.emplace_back(std::move(sphere3));
    //m_objects.emplace_back(std::make_unique<Sphere>(Vector3(), 85.0));

#if 1
    // Add light sources.

    std::unique_ptr<Sphere> light1 = std::make_unique<Sphere>(Vector3(310, 195, 50.0), 5.0, MaterialEmissive(Color(1.0), 0.95));
    //std::unique_ptr<Sphere> light1 = std::make_unique<Sphere>(Vector3(100, 50, 50.0), 5.0, MaterialEmissive(Color(1.0), 0.9));
    ////std::unique_ptr<Sphere> light1 = std::make_unique<Sphere>(Vector3(100, 50, 0.0), 5.0, MaterialEmissive(Color(1.0), 50.0));
    m_objects.emplace_back(std::move(light1));

    std::unique_ptr<Sphere> light2 = std::make_unique<Sphere>(Vector3(-160, -160, 0.0), 5.0, MaterialEmissive(Color(1.0), 0.75));
    ////std::unique_ptr<Sphere> light2 = std::make_unique<Sphere>(Vector3(-250, -130, 0.0), 5.0, MaterialEmissive(Color(1.0), 0.5));
    ////std::unique_ptr<Sphere> light2 = std::make_unique<Sphere>(Vector3(-100, -100, 0.0), 5.0, MaterialEmissive(Color(1.0), 50.0));
    m_objects.emplace_back(std::move(light2));
#endif
}

HitInfo Scene::findNearestHit(const Ray& ray) const
{
	// Data about the nearest intersection, if one is found.
	HitInfo nearestHit;

	// The nearest intersection found.
	VComponent nearestDistance = (std::numeric_limits<VComponent>::max)();

#if 0
	// Check lights in the scene.
	for (const auto& itr : m_lights)
	{
		Intersectable * pIntersectable = dynamic_cast<Intersectable*>(itr.get());
		if (!pIntersectable)
		{
            ATLASSERT(FALSE); continue;
		}

		double distance1 = {}, distance2 = {};

		pIntersectable->intersects(ray, distance1, distance2);

		if (distance1 > 0.0
			&& distance1 < distanceNearest)
		{
			distanceNearest = distance1;

			pIntersected = pIntersectable;
			intersection = ray.m_origin + ray.m_direction * distanceNearest;
		}
	}
#endif

	// Check objects in the scene.
	for (const auto& itr : m_objects)
	{
		VComponent currDistance = {};

		HitInfo currentHit;

		if (itr->hit(ray, currDistance, currentHit))
		{
#if 1
			// On hit, all intersectable objects should return the distance larger than the Epsilon value.
			ATLASSERT(currDistance >= GeometricObject::FloatingEpsilon);
#else
			// On hit, all intersectable objects should return the distance larger than their Epsilon values, which are positive.
			ATLASSERT(currDistance >= 0.0);
#endif

			if (currDistance < nearestDistance)
			{
				nearestDistance = currDistance;

				nearestHit = currentHit;
			}
		}
	}

	return nearestHit;
}

Color Scene::computeIllumination(const HitInfo& hit, const Vector3& rayDirection) const
{
#if 0
	// TODO: temp, simplified.
	return (hit.m_pHit->getMaterial().calculateColor(hit));
#else

	// If the object hit by the ray is itself a light source, simply calculate color emitted by it.
	if (hit.m_pHit->isLight())
	{
		MaterialEmissive *pObjectMat = dynamic_cast<MaterialEmissive *>(hit.m_pHit->getMaterial());
		if (!pObjectMat)
		{
            ATLASSERT(FALSE); return Color();
		}

		return pObjectMat->calcEmissiveColor();
	}

	Material *pMat = hit.m_pHit->getMaterial();

	Vector3 normal = hit.m_normal;

	// Add ambient light contribution.
	Color clrResult = pMat->calcAmbientColor(m_ambientLightIntensity);

	// Create shadow rays for each light in the scene.
	for (const auto& itr : m_objects)
	{
		if (itr->isLight())
		{
			// Direction to the light source.
			Vector3 lightVector = (itr->getCenter() - hit.m_localHitPoint).normalize();

			// Ensure the light source is not behind the hit point's surface.
			if (hit.m_normal.dot(lightVector) <= 0.0)
			{
				continue;
			}

			Ray ray(hit.m_localHitPoint, lightVector);

			HitInfo currHit = findNearestHit(ray);

			if (currHit.isValid())
			{
				if (currHit.m_pHit->isLight())
				{
					// The point is not in shadow.

					// Light source material.
					MaterialEmissive *pLightMat = dynamic_cast<MaterialEmissive *>(itr->getMaterial());
					if (!pLightMat)
					{
                        ATLASSERT(FALSE); return Color();
					}

#if 1
					// Add diffuse light contribution.
					clrResult += pMat->calcDiffuseColor(normal, lightVector, pLightMat->m_emissive, pLightMat->m_intensity);
#endif

					// TODO: fix and uncomment
#if 1
					// Add specular light contribution.
					// TODO: clearly wrong - when summed up with the diffuse contribution, 
					// adds something like a shadow where the light source lits the object.
					// Check for overflow but also note that the specular area is suspiciously large.
					clrResult += pMat->calcSpecularColor(normal, lightVector, pLightMat->m_emissive, pLightMat->m_intensity, rayDirection);
#endif
				}
			}
		}
	}

	return clrResult.clamp();
#endif
}
