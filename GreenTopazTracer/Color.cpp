#include "stdafx.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

// Object to perform tone mapping (empty if we are not using HDR).
extern std::unique_ptr<ToneMapper> g_spToneMapper;

//////////////////////////////////////////////////////////////////////////


Color::Color(ClrComponent component)
	: m_red(component), m_green(component), m_blue(component)
{
}

Color::Color(ClrComponent red, ClrComponent green, ClrComponent blue)
	: m_red(red), m_green(green), m_blue(blue)
{
}

COLORREF Color::toBGR() const
{
    if (g_spToneMapper)
    {
#if 1
        Color mapped = g_spToneMapper->convert(*this);
#else
        // TODO: don't delete - seems to be faster.

        // Exposure tone mapping.

        const ClrComponent exposure = 0.1;

        Color mapped = Color(1.0) - Color(exp(-m_red * exposure), exp(-m_green * exposure), exp(-m_blue * exposure));

        // Gamma correction.
        const ClrComponent gamma = 2.2;
        mapped = mapped.raiseToPower(Vector3(1.0 / gamma));
#endif

        return RGB(mapped.m_blue * 255, mapped.m_green * 255, mapped.m_red * 255);
    }
    else
    {
        return RGB(m_blue * 255, m_green * 255, m_red * 255);
    }
}

COLORREF Color::toRGB() const
{
    if (g_spToneMapper)
    {
#if 1
        Color mapped = g_spToneMapper->convert(*this);
#else
        // TODO: don't delete - seems to be faster.

        // Exposure tone mapping.

        const ClrComponent exposure = 0.1;

        Color mapped = Color(1.0) - Color(exp(-m_red * exposure), exp(-m_green * exposure), exp(-m_blue * exposure));

        // Gamma correction.
        const ClrComponent gamma = 2.2;
        mapped = mapped.raiseToPower(Vector3(1.0 / gamma));
#endif

        return RGB(mapped.m_red * 255, mapped.m_green * 255, mapped.m_blue * 255);
    }
    else
    {
        return RGB(m_red * 255, m_green * 255, m_blue * 255);
    }
}

Color Color::operator+(const Color& other) const
{
	return Color(m_red + other.m_red, m_green + other.m_green, m_blue + other.m_blue);
}

Color& Color::operator+=(const Color& other)
{
	m_red   += other.m_red;
	m_green += other.m_green;
	m_blue  += other.m_blue;

	return (*this);
}

Color Color::operator-(const Color& other) const
{
    return Color(m_red - other.m_red, m_green - other.m_green, m_blue - other.m_blue);
}

Color Color::operator-() const
{
    return Color(-m_red, -m_green, -m_blue);
}

Color Color::operator/(int divisor) const
{
	return Color(m_red / divisor, m_green / divisor, m_blue / divisor);
}

Color Color::operator/(const Color& divisor) const
{
    return Color(m_red / divisor.m_red, m_green / divisor.m_green, m_blue / divisor.m_blue);
}

Color Color::operator*(ClrComponent val) const
{
	return Color(m_red * val, m_green * val, m_blue * val);
}

Color Color::operator*(const Color& other) const
{
	return Color(m_red * other.m_red, m_green * other.m_green, m_blue * other.m_blue);
}

Color Color::raiseToPower(const Vector3& v) const
{
    return Color(pow(m_red, v.m_x), pow(m_green, v.m_y), pow(m_blue, v.m_z));
}

Color Color::exponentiate() const
{
    return Color(exp(m_red), exp(m_green), exp(m_blue));
}

bool Color::isBlack() const
{
	return (   0.0 == m_red
			&& 0.0 == m_green
			&& 0.0 == m_blue);
}

Color& Color::clamp()
{
    // Clamping is done if we are not using tone mapping.
    if (!g_spToneMapper)
    {
        if (m_red < 0.0)
        {
            m_red = 0.0;
        }
        else if (m_red > 1.0)
        {
            m_red = 1.0;
        }

        if (m_green < 0.0)
        {
            m_green = 0.0;
        }
        else if (m_green > 1.0)
        {
            m_green = 1.0;
        }

        if (m_blue < 0.0)
        {
            m_blue = 0.0;
        }
        else if (m_blue > 1.0)
        {
            m_blue = 1.0;
        }
    }   // Clamping is done if we are not using tone mapping.

    return (*this);
}
