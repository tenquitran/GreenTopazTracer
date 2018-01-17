#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Vector3::Vector3()
	: m_x{}, m_y{}, m_z{}
{
}

Vector3::Vector3(VComponent x)
	: m_x(x), m_y(x), m_z(x)
{
}

Vector3::Vector3(VComponent x, VComponent y, VComponent z)
	: m_x(x), m_y(y), m_z(z)
{
}

VComponent Vector3::length() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector3 Vector3::normalize() const
{
	VComponent reciprocal = 1 / this->length();

	return Vector3(m_x * reciprocal, m_y * reciprocal, m_z * reciprocal);
}
