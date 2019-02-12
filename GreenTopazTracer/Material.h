#pragma once


namespace GreenTopazTracerApp
{
	// Base class for material.
	class Material
	{
	public:
		explicit Material(EMaterialType type);

		virtual ~Material();

		// Get type of the material.
        EMaterialType getType() const;

    private:
        // Type of the material.
        const EMaterialType m_type = { EMaterialType::Undefined };
	};
}
