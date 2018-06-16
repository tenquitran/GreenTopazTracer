#pragma once


namespace GreenTopazTracerApp
{
	class GeometricObject
	{
	public:
		explicit GeometricObject(const Vector3& center);

		virtual ~GeometricObject();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) = 0;

		virtual const Material& getMaterial() const = 0;

	protected:
		// For most geometric objects, a center.
		// For a plane, any point that belong to a plane.
		Vector3 m_center;

		// Epsilon for intersection calculations, etc.
		static const VComponent Epsilon;
	};

	typedef std::unique_ptr<GeometricObject> GeometricObjectUPtr;
}
