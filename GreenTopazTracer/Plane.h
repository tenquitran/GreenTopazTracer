#pragma once


namespace GreenTopazTracerApp
{
	class Plane
		: public GeometricObject
		//,public HasMaterial
	{
	public:
		Plane(const Vector3& center, const Vector3& normal, const MaterialPhong& material);

		virtual ~Plane();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) override;

#if 1
		virtual const Material& getMaterial() const override;
#endif

	private:
		// Normal to the plane.
		Vector3 m_normal;

		MaterialPhong m_material;
	};
}
