#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


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
	VComponent len = this->length();

	// Normalization is required (and possible) only if the vector length is non-zero.
	if (0.0 != len)
	{
		VComponent reciprocal = 1 / this->length();

		return Vector3(m_x * reciprocal, m_y * reciprocal, m_z * reciprocal);
	}
	
	return Vector3();
}

bool Vector3::operator==(const Vector3& other) const
{
	return (   m_x == other.m_x 
		    && m_y == other.m_y 
		    && m_z == other.m_z);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return (   m_x != other.m_x
		    || m_y != other.m_y
		    || m_z != other.m_z);
}

Vector3& Vector3::operator=(const Vector3& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
	m_z = other.m_z;

	return (*this);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-m_x, -m_y, -m_z);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	m_z += other.m_z;

	return (*this);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	m_z -= other.m_z;

	return (*this);
}

Vector3 Vector3::operator*(VComponent val) const
{
	return Vector3(m_x * val, m_y * val, m_z * val);
}

Vector3& Vector3::operator*=(VComponent val)
{
	m_x *= val;
	m_y *= val;
	m_z *= val;

	return (*this);
}

Vector3 Vector3::operator/(VComponent val) const
{
	if (0.0 == val)
	{
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Divide by zero");
	}

	VComponent inverse = 1 / val;

	return Vector3(m_x * inverse, m_y * inverse, m_z * inverse);
}

Vector3& Vector3::operator/=(VComponent val)
{
	if (0.0 == val)
	{
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"Divide by zero");
	}

	VComponent inverse = 1 / val;

	m_x *= inverse;
	m_y *= inverse;
	m_z *= inverse;

	return (*this);
}

VComponent Vector3::dot(const Vector3& other) const
{
	return (m_x * other.m_x + m_y * other.m_y + m_z * other.m_z);
}

VComponent Vector3::dot(const Vector3& a, const Vector3& b)
{
	return (a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z);
}

Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(m_y * other.m_z - m_z * other.m_y,
				   m_z * other.m_x - m_x * other.m_z,
				   m_x * other.m_y - m_y * other.m_x);
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	return Vector3(a.m_y * b.m_z - a.m_z * b.m_y,
				   a.m_z * b.m_x - a.m_x * b.m_z,
				   a.m_x * b.m_y - a.m_y * b.m_x);
}
