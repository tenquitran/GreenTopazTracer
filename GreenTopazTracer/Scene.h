#pragma once


namespace GreenTopazTracerApp
{
	// Contains object to ray trace.
	class Scene
	{
	public:
		explicit Scene(const Color& backgroundColor);

		virtual ~Scene();

		Color getBackgroundColor() const
		{
			return m_backgroundColor;
		}

		// Find the nearest intersection of the ray with the scene objects.
		// Parameters: ray - ray to intersect.
		// Return: intersection data. Call isValid() to check if there was an actual intersection.
		HitInfo findNearestHit(const Ray& ray) const;

        // Parameters: hit - hit point data;
        //             rayDirection - direction of the ray.
		Color computeIllumination(const HitInfo& hit, const Vector3& rayDirection) const;

	private:
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

        // Create a scene suitable for Phong lighting demonstration.
        void createPhongScene();

	private:
		// Objects in the scene, including light sources.
		std::vector<GeometricObjectUPtr> m_objects;

#if 0
		// Light sources.
		std::vector<GeometricObjectUPtr> m_lights;
#endif

		Color m_backgroundColor;

        ClrComponent m_ambientLightIntensity = { 0.2 };
	};
}
