#pragma once


namespace GreenTopazTracerApp
{
	// Color component.
	typedef double ClrComponent;


#pragma pack(push, 1)
	struct Color
	{
	public:
		Color() = default;

		explicit Color(ClrComponent component);

		Color(ClrComponent red, ClrComponent green, ClrComponent blue);

		COLORREF toBGR() const;

		// Convert color values to the RGB format used in Windows.
		COLORREF toRGB() const;

		Color operator+(const Color& other) const;

		Color& operator+=(const Color& other);

        Color operator-(const Color& other) const;

        // Unary minus.
        Color operator-() const;

        Color operator/(int divisor) const;

        Color operator/(const Color& divisor) const;

		Color operator*(ClrComponent val) const;

		Color operator*(const Color& other) const;

        Color raiseToPower(const Vector3& v) const;

        Color exponentiate() const;

		bool isBlack() const;

		Color& clamp();

	public:
        ClrComponent m_red   = {};
        ClrComponent m_green = {};
        ClrComponent m_blue  = {};
	};
#pragma pack(pop)


	// Multiplication by ClrComponentType on the left.
	inline Color operator*(ClrComponent val, const Color& clr)
	{
		return (clr * val);
	}
}
