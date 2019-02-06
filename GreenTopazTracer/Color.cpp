#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Color::Color()
	: m_red{}, m_green{}, m_blue{}
{
}

Color::Color(ClrComponentType component)
	: m_red(component), m_green(component), m_blue(component)
{
}

Color::Color(ClrComponentType red, ClrComponentType green, ClrComponentType blue)
	: m_red(red), m_green(green), m_blue(blue)
{
}

COLORREF Color::toBGR() const
{
	return RGB(m_blue * 255, m_green * 255, m_red * 255);
}

COLORREF Color::toRGB() const
{
	return RGB(m_red * 255, m_green * 255, m_blue * 255);
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

Color Color::operator/(int divisor) const
{
	return Color(m_red / divisor, m_green / divisor, m_blue / divisor);
}

Color Color::operator*(ClrComponentType val) const
{
	return Color(m_red * val, m_green * val, m_blue * val);
}

Color Color::operator*(const Color& other) const
{
	return Color(m_red * other.m_red, m_green * other.m_green, m_blue * other.m_blue);
}

bool Color::isBlack() const
{
	return (   0.0 == m_red
			&& 0.0 == m_green
			&& 0.0 == m_blue);
}

Color& Color::clamp()
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

	return (*this);
}
