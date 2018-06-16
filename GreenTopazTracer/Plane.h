#pragma once


namespace GreenTopazTracerApp
{
	class Plane
		: public GeometricObject
	{
	public:
		// Solid object.
		Plane(const Vector3& center, const Vector3& normal, const MaterialPhong& material);

		// Light source.
		Plane(const Vector3& center, const Vector3& normal, const MaterialEmissive& material);

		virtual ~Plane();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) override;

		virtual const Material& getMaterial() const override;

	private:
		// Normal to the plane.
		Vector3 m_normal;

		std::unique_ptr<Material> m_spMaterial;
	};
}
