#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Plane::Plane(const Vector3& center, const Vector3& normal, const MaterialPhong& material)
	: GeometricObject(center, false), 
	  m_normal(normal)
{
	m_spMaterial = std::make_unique<MaterialPhong>(material);
}

Plane::Plane(const Vector3& center, const Vector3& normal, const MaterialEmissive& material)
	: GeometricObject(center, true),
	  m_normal(normal)
{
	m_spMaterial = std::make_unique<MaterialEmissive>(material);
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

const Material& Plane::getMaterial() const
{
	return *m_spMaterial;
}
