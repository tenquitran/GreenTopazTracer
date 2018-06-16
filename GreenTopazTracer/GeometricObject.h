#pragma once


namespace GreenTopazTracerApp
{
	class GeometricObject
	{
	public:
		GeometricObject(const Vector3& center, bool isLight);

		virtual ~GeometricObject();

		// Intersection ("hit") test.
		// Parameters: ray - ray to test the intersection with;
		//             tNearest - nearest intersection point;
		//             hitInfo - information about the intersection point.
		virtual bool hit(const Ray& ray, VComponent& tNearest, HitInfo& hitInfo) = 0;

		virtual const Material& getMaterial() const = 0;

		// Returns true if the object is the light source.
		bool isLight() const
		{
			return m_isLight;
		}

	protected:
		// For most geometric objects, a center.
		// For a plane, any point that belong to a plane.
		Vector3 m_center;

		// Epsilon for intersection calculations, etc.
		static const VComponent Epsilon;

		// true if the object is the light source.
		bool m_isLight;
	};

	typedef std::unique_ptr<GeometricObject> GeometricObjectUPtr;
}
