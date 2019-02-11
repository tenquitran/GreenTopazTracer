#pragma once


namespace GreenTopazTracerApp
{
	// Color component data type.
	typedef double ClrComponentType;

#pragma pack(push, 1)
	struct Color
	{
	public:
		Color() = default;

		explicit Color(ClrComponentType component);

		Color(ClrComponentType red, ClrComponentType green, ClrComponentType blue);

		COLORREF toBGR() const;

		// Convert color values to the RGB format used in Windows.
		COLORREF toRGB() const;

		Color operator+(const Color& other) const;

		Color& operator+=(const Color& other);

		Color operator/(int divisor) const;

		Color operator*(ClrComponentType val) const;

		Color operator*(const Color& other) const;

		bool isBlack() const;

		Color& clamp();

	public:
        ClrComponentType m_red   = {};
        ClrComponentType m_green = {};
        ClrComponentType m_blue  = {};
	};
#pragma pack(pop)


	// Multiplication by ClrComponentType on the left.
	inline Color operator*(ClrComponentType val, const Color& clr)
	{
		return (clr * val);
	}
}
