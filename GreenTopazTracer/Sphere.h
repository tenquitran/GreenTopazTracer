#pragma once


namespace GreenTopazTracerApp
{
	class Sphere
		: public GeometricObject
	{
	public:
		// Solid sphere.
		Sphere(const Vector3& center, VComponent radius, const MaterialPhong& material);

		// Light source.
		Sphere(const Vector3& center, VComponent radius, const MaterialEmissive& material);

		virtual ~Sphere();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) override;

		virtual const Material& getMaterial() const override;

	private:
		VComponent m_radius;

		std::unique_ptr<Material> m_spMaterial;
	};
}
