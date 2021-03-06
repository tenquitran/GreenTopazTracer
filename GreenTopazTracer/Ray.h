#pragma once


namespace GreenTopazTracerApp
{
	struct Ray
	{
	public:
		Ray();

		Ray(const Vector3& origin, const Vector3& direction/*, const Color& intensity*/);

		// TODO: don't delete
#if 0
		// Returns true if the ray intensity is too low to significantly contribute to the scene rendering.
		bool isIntensityTooLow() const;
#endif

	public:
		// Origin of the ray.
		Vector3 m_origin;
		
		// Normalized direction of the ray.
		Vector3 m_direction;

		// TODO: don't delete
#if 0
		// Ray intensity.
		Color m_intensity;

		// If the ray intensity is lower than the threshold, the ray is considered insignificant.
		static const ClrComponentType IntensityThreshold;
#endif
	};
}
