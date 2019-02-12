#pragma once


namespace GreenTopazTracerApp
{
	// Single-colored Phong material.
	class MaterialPhong
		: public Material
	{
	public:
		MaterialPhong(const Color& ambient, const Color& diffuse, const Color& specular, 
			double specularity = 0.0, double reflectivity = 0.0, double opacity = 1.0, double refractionIndex = 1.0);

		virtual ~MaterialPhong();

		// Calculate ambient color contribution.
		// Parameters: ambIntensity - intensity of the scene's ambient light.
		Color calcAmbientColor(ClrComponentType ambIntensity) const;

		// Calculate diffuse color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light.
		Color calcDiffuseColor(const Vector3& normal, const Vector3& lightVector, 
			const Color& lightColor, double lightBrightness) const;

		// Calculate specular color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light;
		//             rayDirection - direction of the tracing ray.
		Color calcSpecularColor(const Vector3& normal, const Vector3& lightVector,
			const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const;

		bool isSpecular() const
		{
			return (m_specularity > 0.0);
		}

		bool isReflective() const
		{
			return (m_reflectivity > 0.0);
		}

		bool isTransparent() const
		{
			return (m_opacity < 1.0);
		}

	private:
		Color m_ambientColor;

		Color m_diffuseColor;

		Color m_specularColor;

		// Specular reflection coefficient (shininess or glossiness).
		// Very large (e.g. 1250) for small and bright specular reflections, 
		// relatively small (e.g. 2) for larger but not so bright specular reflections.
        double m_specularity = {};

		// Reflectivity coefficient for mirror-like reflections.
		// Not the same as specularity.
        double m_reflectivity = {};

		// From 0.0 (completely transparent) to 1.0 (completely opaque).
        double m_opacity = { 1.0 };

        double m_refractionIndex = { 1.0 };
	};
}
