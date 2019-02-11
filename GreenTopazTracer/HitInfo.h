#pragma once


namespace GreenTopazTracerApp
{
	class GeometricObject;


	// Information about the intersection ("hit") point.
	struct HitInfo
	{
	public:
		HitInfo() = default;

		// Returns true if there was an actual intersection with an object.
		bool isValid() const
		{
			return (nullptr != m_pHit);
		}

	public:
		// Normal at the intersection point.
		Vector3 m_normal;

		// Intersection point in world coordinates (for texture transformations).
		Vector3 m_localHitPoint;

		// The object intersected (or NULL if there is no intersection).
        GeometricObject const * m_pHit = { nullptr };
	};
}
