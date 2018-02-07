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
