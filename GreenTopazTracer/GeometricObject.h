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

		// TODO: temp. The object material info should be there.
		void setColor(ClrComponentType r, ClrComponentType g, ClrComponentType b)
		{
			m_color.m_red   = r;
			m_color.m_green = g;
			m_color.m_blue  = b;
		}

		// TODO: temp. The object material info should be there.
		Color getColor() const
		{
			return m_color;
		}

	protected:
		// For most geometric objects, a center.
		// For a plane, any point that belong to a plane.
		Vector3 m_center;

		// TODO: temp. The object material info should be there.
		Color m_color;
	};

	typedef std::unique_ptr<GeometricObject> GeometricObjectUPtr;
}
