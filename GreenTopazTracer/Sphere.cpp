#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Sphere::Sphere(const Vector3& center, VComponent radius, const MaterialPhong& material)
	: GeometricObject(center), 
	  m_radius(radius)
{
	m_spMaterial = std::make_unique<MaterialPhong>(material);
}

Sphere::Sphere(const Vector3& center, VComponent radius, const MaterialEmissive& material)
	: GeometricObject(center, true),
	  m_radius(radius)
{
	m_spMaterial = std::make_unique<MaterialEmissive>(material);
}

Sphere::~Sphere()
{
}

bool Sphere::hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) const
{
	VComponent t;
	Vector3 temp = ray.m_origin - m_center;

	VComponent a = Vector3::dot(ray.m_direction, ray.m_direction);
	VComponent b = Vector3::dot(2.0 * temp, ray.m_direction);
	VComponent c = Vector3::dot(temp, temp) - m_radius * m_radius;
	VComponent discr = b * b - 4.0 * a * c;

	if (discr < 0.0)
	{
		return false;
	}

	VComponent e = sqrt(discr);
	VComponent denominator = 2.0 * a;

	// Smaller root of the quadratic equation.
	t = (-b - e) / denominator;

	if (t > FloatingEpsilon)
	{
		tNearest = t;
		hitInfo.m_normal = (temp + t * ray.m_direction) / m_radius;
		hitInfo.m_localHitPoint = ray.m_origin + t * ray.m_direction;
		hitInfo.m_pHit = this;
		return true;
	}

	// Larger root of the quadratic equation.
	t = (-b + e) / denominator;

	if (t > FloatingEpsilon)
	{
		tNearest = t;
		hitInfo.m_normal = (temp + t * ray.m_direction) / m_radius;
		hitInfo.m_localHitPoint = ray.m_origin + t * ray.m_direction;
		hitInfo.m_pHit = this;
		return true;
	}

	return false;
}

Material* Sphere::getMaterial() const
{
	return m_spMaterial.get();
}
