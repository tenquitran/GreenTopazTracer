#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

// Epsilon for intersection calculations, etc.
const VComponent Plane::EPSILON = 0.001;

//////////////////////////////////////////////////////////////////////////


Plane::Plane(const Vector3& center, const Vector3& normal)
	: GeometricObject(center), m_normal(normal)
{
}

Plane::~Plane()
{
}

bool Plane::hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo)
{
	VComponent t = Vector3::dot(m_center - ray.m_origin, m_normal) / Vector3::dot(ray.m_direction, m_normal);

	if (t > EPSILON)
	{
		tNearest = t;
		hitInfo.m_normal = m_normal;
		hitInfo.m_localHitPoint = ray.m_origin + t * ray.m_direction;

		return true;
	}

	return false;
}
