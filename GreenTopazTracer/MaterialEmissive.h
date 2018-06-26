#pragma once


namespace GreenTopazTracerApp
{
	class MaterialEmissive
		: public Material
	{
	public:
		MaterialEmissive(const Color& emissive, double intensity);

		virtual ~MaterialEmissive();

		// Calculate color at the intersection point.
		virtual Color calculateColor(const HitInfo& hitInfo) const override;

		virtual EMaterialType getType() const override
		{
			return EMaterialType::Emissive;
		}

	public:
		Color m_emissive;

		double m_intensity;
	};
}
