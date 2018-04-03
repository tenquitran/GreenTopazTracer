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

COLORREF Color::toRGB() const
{
	return RGB(m_red * 255, m_green * 255, m_blue * 255);
}

Color Color::operator+(const Color& other)
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

Color Color::operator/(int divisor)
{
	return Color(m_red / divisor, m_green / divisor, m_blue / divisor);
}
