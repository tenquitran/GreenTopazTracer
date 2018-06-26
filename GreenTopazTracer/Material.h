#pragma once


namespace GreenTopazTracerApp
{
	// Base class for material.
	class Material
	{
	public:
		Material();

		virtual ~Material();

		// Calculate color at the intersection point.
		virtual Color calculateColor(const HitInfo& hitInfo) const = 0;

		// Get type of the material.
		virtual EMaterialType getType() const = 0;
	};
}
