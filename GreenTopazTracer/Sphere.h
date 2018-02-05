#pragma once


namespace GreenTopazTracerApp
{
	class Sphere
		: public GeometricObject
	{
	public:
		Sphere(const Vector3& center, VComponent radius);

		virtual ~Sphere();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) override;

	private:
		VComponent m_radius;

		// Epsilon for intersection calculations, etc.
		static const VComponent Epsilon;
	};
}
