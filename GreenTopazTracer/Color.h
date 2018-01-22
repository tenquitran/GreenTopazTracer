#pragma once


namespace GreenTopazTracerApp
{
	// Color component data type.
	typedef double ClrComponentType;


	struct Color
	{
	public:
		Color();

		explicit Color(ClrComponentType component);

		Color(ClrComponentType red, ClrComponentType green, ClrComponentType blue);

	public:
		ClrComponentType m_red;
		ClrComponentType m_green;
		ClrComponentType m_blue;
	};
}
