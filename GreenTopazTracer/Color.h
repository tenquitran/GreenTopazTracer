#pragma once


namespace GreenTopazTracerApp
{
	// Color component data type.
	typedef double ClrComponentType;

#pragma pack(push, 1)
	struct Color
	{
	public:
		Color();

		explicit Color(ClrComponentType component);

		Color(ClrComponentType red, ClrComponentType green, ClrComponentType blue);

		// Convert color values to the RGB format used in Windows.
		COLORREF toRGB() const;

		Color operator+(const Color& other);

		Color& operator+=(const Color& other);

		Color operator/(int divisor);

		//Color& operator/=(const Color& other);

	public:
		ClrComponentType m_red;
		ClrComponentType m_green;
		ClrComponentType m_blue;
	};
#pragma pack(pop)
}
