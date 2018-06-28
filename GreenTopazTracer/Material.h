#pragma once


namespace GreenTopazTracerApp
{
	// Base class for material.
	class Material
	{
	public:
		Material();

		virtual ~Material();

#if 0
		// Calculate color at the intersection point.
		virtual Color calculateColor(const HitInfo& hitInfo) const = 0;
#else
		// Calculate ambient color contribution.
		// Parameters: ambIntensity - intensity of the scene's ambient light.
		virtual Color calcAmbientColor(ClrComponentType ambIntensity) const = 0;

		// Calculate diffuse color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light.
		virtual Color calcDiffuseColor(const Vector3& normal, const Vector3& lightVector,
			const Color& lightColor, double lightBrightness) const = 0;

		// Calculate specular color contribution.
		// Parameters: normal - normal at the hit point;
		//             lightVector - direction to the light source (normalized);
		//             lightColor - color of the light;
		//             lightBrightness - brightness of the light;
		//             rayDirection - direction of the tracing ray.
		virtual Color calcSpecularColor(const Vector3& normal, const Vector3& lightVector, 
			const Color& lightColor, double lightBrightness, const Vector3& rayDirection) const = 0;
#endif

		// Get type of the material.
		virtual EMaterialType getType() const = 0;
	};
}
