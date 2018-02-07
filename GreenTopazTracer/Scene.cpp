#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene()
	: m_backgroundColor(0.0, 0.64, 0.91)    // light blue
{
	// Add a sphere with the center at the origin

	std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3(), 85.0);
	sphere1->setColor(0.94, 0.28, 0.31);    // red (not too bright)

	m_objects.emplace_back(std::move(sphere1));
	//m_objects.emplace_back(std::make_unique<Sphere>(Vector3(), 85.0));
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
			// On hit, all intersectable objects should return the distance larger than their Epsilon values, which are positive.
			assert(currDistance >= 0.0);

			if (currDistance < nearestDistance)
			{
				nearestDistance = currDistance;

				nearestHit = currentHit;
			}
		}
	}

	return nearestHit;
}
