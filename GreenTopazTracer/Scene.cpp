#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene(const Color& backgroundColor)
	: m_backgroundColor(backgroundColor), m_ambientLightIntensity(0.2)
{
#if 0
	// Add a sphere with the center at the origin.
	std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3(), 85.0);
#else
	Color red(0.94, 0.28, 0.31);    // red (not too bright)

	// A sphere with the center at the top left corner.
	std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3(-400.0, -300.0, 0.0), 120.0, MaterialPhong(red, red, red, 0.0));
	//sphere1->setColor(0.94, 0.28, 0.31);    // red (not too bright)

	Color darkBlue(0.0, 0.0, 0.63);

	// A sphere with the center at the origin.
	std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3(), 85.0, MaterialPhong(darkBlue, darkBlue, darkBlue, 0.0));
	//sphere2->setColor(0.0, 0.0, 0.63);    // dark blue
#endif
	
	m_objects.emplace_back(std::move(sphere1));
	m_objects.emplace_back(std::move(sphere2));
	//m_objects.emplace_back(std::make_unique<Sphere>(Vector3(), 85.0));

#if 1
	// Add light sources.

	std::unique_ptr<Sphere> light1 = std::make_unique<Sphere>(Vector3(100, 50, 0.0), 5.0, MaterialEmissive(Color(1.0), 1.0));
	//std::unique_ptr<LightSource> light1 = std::make_unique<LightSource>(Vector3(100, 50, 0.0), 5.0, MaterialEmissive(Color(1.0), 1.0));

	m_objects.emplace_back(std::move(light1));
	//m_lights.emplace_back(std::move(light1));
#endif
}

Scene::~Scene()
{
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
			assert(false); continue;
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
			assert(currDistance >= GeometricObject::FloatingEpsilon);
#else
			// On hit, all intersectable objects should return the distance larger than their Epsilon values, which are positive.
			assert(currDistance >= 0.0);
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

Color Scene::computeIllumination(const HitInfo& hit) const
{
#if 0
	// TODO: temp, simplified.
	return (hit.m_pHit->getMaterial().calculateColor(hit));
#else

	// TODO: if the hit point is at the light source, use the emissive color, etc.

	// TODO: temp
#if 0
	MaterialPhong *pMat = dynamic_cast<MaterialPhong*>(hit.m_pHit->getMaterial());

	switch (hit.m_pHit->getMaterial()->getType())
	{
	case EMaterialType::Phong:
		;
		break;
	case EMaterialType::Emissive:
		;
		break;
	default:
		assert(false); break;
	}
#endif

	// Add ambient light contribution.
	Color clrResult = m_ambientLightIntensity * hit.m_pHit->getMaterial()->calculateColor(hit);

	// Create shadow rays for each light in the scene.
	for (const auto& itr : m_objects)
	{
		if (itr->isLight())
		{
			// Direction to the light source.
			Vector3 direction = (itr->getCenter() - hit.m_localHitPoint).normalize();

			// Ensure the light source is not behind the hit point's surface.
			if (hit.m_normal.dot(direction) <= 0.0)
			{
				continue;
			}

			Ray ray(hit.m_localHitPoint, direction);

			HitInfo currHit = findNearestHit(ray);

			if (currHit.isValid())
			{
				if (currHit.m_pHit->isLight())
				{
					// The point is not in shadow
					
					// Add diffuse light contribution.
					;

					// Add specular light contribution.
					;

					// TODO: temp, simplified.
					//return (hit.m_pHit->getMaterial().calculateColor(hit));
				}
			}
		}
	}

	return clrResult;
#endif
}
