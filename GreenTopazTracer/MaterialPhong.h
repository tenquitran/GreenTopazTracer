#pragma once


namespace GreenTopazTracerApp
{
	// Single-colored Phong material.
	class MaterialPhong
		: public Material
	{
	public:
#if 0
		MaterialPhong();
#endif

		MaterialPhong(const Color& ambient, const Color& diffuse, const Color& specular, 
			double specularity, double reflectivity = 0.0, double opacity = 1.0, double refractionIndex = 1.0);

		virtual ~MaterialPhong();

		// Calculate color at the intersection point.
		virtual Color calculateColor(const HitInfo& hitInfo) const override;

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

	public:
		Color m_ambientColor;

		Color m_diffuseColor;

		Color m_specularColor;

		// Specular reflection coefficient (shininess or glossiness).
		// Very large (e.g. 1250) for small and bright specular reflections, 
		// relatively small (e.g. 2) for larger but not so bright specular reflections.
		double m_specularity;

		// Reflectivity coefficient for mirror-like reflections.
		// Not the same as specularity.
		double m_reflectivity;

		// From 0.0 (completely transparent) to 1.0 (completely opaque).
		double m_opacity;

		double m_refractionIndex;
	};
}
