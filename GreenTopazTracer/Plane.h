#pragma once


namespace GreenTopazTracerApp
{
	class Plane
		: public GeometricObject
	{
	public:
		Plane(const Vector3& center, const Vector3& normal);

		virtual ~Plane();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) override;

	private:
		// Normal to the plane.
		Vector3 m_normal;

		// Epsilon for intersection calculations, etc.
		static const VComponent Epsilon;
	};
}
