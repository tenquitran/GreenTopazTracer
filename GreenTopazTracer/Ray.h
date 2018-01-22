#pragma once


namespace GreenTopazTracerApp
{
	struct Ray
	{
	public:
		Ray();

		Ray(const Vector3& origin, const Vector3& direction, const Color& intensity);

		// Returns true if the ray intensity is too low to significantly contribute to the scene rendering.
		bool hasTooLowIntensity() const;

	public:
		// Origin of the ray.
		Vector3 m_origin;
		
		// Normalized direction of the ray.
		Vector3 m_direction;

		// Ray intensity.
		Color m_intensity;

		// If the ray intensity is lower than the threshold, the ray is considered insignificant.
		static const ClrComponentType INTENSITY_THRESHOLD;
	};
}
