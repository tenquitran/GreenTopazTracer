#pragma once


namespace GreenTopazTracerApp
{
	class MaterialEmissive
		: public Material
	{
	public:
		MaterialEmissive(const Color& emissive, double intensity);

		virtual ~MaterialEmissive();

		// Calculate the emissive color.
		Color calcEmissiveColor() const;

	public:
		Color m_emissive;

		// Light intensity. Can exceed 1.0;
        double m_intensity = {};
	};
}
