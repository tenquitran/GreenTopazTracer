#pragma once


namespace GreenTopazTracerApp
{
	class MaterialEmissive
		: public Material
	{
	public:
		MaterialEmissive(const Color& emissive, double intensity);

		virtual ~MaterialEmissive();

#if 0
		// Calculate color at the intersection point.
		virtual Color calculateColor(const HitInfo& hitInfo) const override;
#else
		// Calculate ambient color contribution.
		// Parameters: ambIntensity - intensity of the scene's ambient light.
		virtual Color calcAmbientColor(ClrComponentType ambIntensity) const override;

		// Calculate diffuse color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light.
		virtual Color calcDiffuseColor(const Vector3& normal, const Vector3& lightVector,
			const Color& lightColor, double lightBrightness) const override;

		// Calculate specular color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light;
		//             rayDirection - direction of the tracing ray.
		virtual Color calcSpecularColor(const Vector3& normal, const Vector3& lightVector,
			const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const override;

		// Calculate color of the light source material.
		Color calcEmissiveColor() const;
#endif

		virtual EMaterialType getType() const override
		{
			return EMaterialType::Emissive;
		}

	public:
		Color m_emissive;

		// Light intensity. Can exceed 1.0;
        double m_intensity = {};
	};
}
