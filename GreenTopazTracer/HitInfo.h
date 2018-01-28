#pragma once


namespace GreenTopazTracerApp
{
	// Information about the intersection ("hit") point.
	struct HitInfo
	{
	public:
		HitInfo();

	public:
		// Normal at the intersection point.
		Vector3 m_normal;

		// Intersection point in world coordinates (for texture transformations).
		Vector3 m_localHitPoint;
	};
}
