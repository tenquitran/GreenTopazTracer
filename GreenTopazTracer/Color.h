#pragma once


namespace GreenTopazTracerApp
{
	// Color component data type.
	typedef double ClrComponentType;


	struct Color
	{
	public:
		Color();

		explicit Color(ClrComponentType c);

		Color(ClrComponentType r, ClrComponentType g, ClrComponentType b);

	private:
		ClrComponentType m_r;
		ClrComponentType m_g;
		ClrComponentType m_b;
	};
}
