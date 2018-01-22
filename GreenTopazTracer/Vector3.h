#pragma once


namespace GreenTopazTracerApp
{
	// Vector component data type.
	typedef double VComponent;


	struct Vector3
	{
	public:
		inline Vector3();

		inline explicit Vector3(VComponent x);

		inline Vector3(VComponent x, VComponent y, VComponent z);

		// Get vector length, or magnitude.
		inline VComponent length() const;

		// Return normalized vector.
		inline Vector3 normalize() const;

		// Check for equality.
		inline bool operator==(const Vector3& other) const;

		// Check for inequality.
		inline bool operator!=(const Vector3& other) const;
		
		// Assignment operator.
		inline Vector3& operator=(const Vector3& other);

		// Return the negative of the vector.
		inline Vector3 operator-() const;

		// Arithmetic operations and the corresponding combined assignment operators.

		inline Vector3 operator+(const Vector3& other) const;

		inline Vector3& operator+=(const Vector3& other);

		inline Vector3 operator-(const Vector3& other) const;

		inline Vector3& operator-=(const Vector3& other);

		inline Vector3 operator*(VComponent val) const;

		inline Vector3& operator*=(VComponent val);

		// Throws: Exception
		inline Vector3 operator/(VComponent val) const;

		inline Vector3& operator/=(VComponent val);

		// Dot product: member version.
		inline VComponent dot(const Vector3& other) const;

		// Dot product: non-member version.
		inline static VComponent dot(const Vector3& a, const Vector3& b);

		// Cross product: member version.
		inline Vector3 cross(const Vector3& other) const;

		// Cross product: non-member version.
		inline static Vector3 cross(const Vector3& a, const Vector3& b);

	public:
		VComponent m_x;
		VComponent m_y;
		VComponent m_z;
	};
}

#include "Vector3.inl"
