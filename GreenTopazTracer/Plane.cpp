#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Plane::Plane(const Vector3& center, const Vector3& normal, const MaterialPhong& material)
	: GeometricObject(center), 
	  //HasMaterial(material),
	  m_normal(normal), m_material(material)
{
}

Plane::~Plane()
{
}

bool Plane::hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo)
{
	VComponent t = Vector3::dot(m_center - ray.m_origin, m_normal) / Vector3::dot(ray.m_direction, m_normal);

	if (t > Epsilon)
	{
		tNearest = t;
		hitInfo.m_normal = m_normal;
		hitInfo.m_localHitPoint = ray.m_origin + t * ray.m_direction;

		return true;
	}

	return false;
}

#if 1
const Material& Plane::getMaterial() const
{
	return m_material;
}
#endif
