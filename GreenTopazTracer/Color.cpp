#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Color::Color()
	: m_r{}, m_g{}, m_b{}
{
}

Color::Color(ClrComponentType c)
	: m_r(c), m_g(c), m_b(c)
{
}

Color::Color(ClrComponentType r, ClrComponentType g, ClrComponentType b)
	: m_r(r), m_g(g), m_b(b)
{
}
