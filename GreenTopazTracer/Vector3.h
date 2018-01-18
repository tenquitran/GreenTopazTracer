#pragma once


namespace GreenTopazTracerApp
{
	// Vector component data type.
	typedef double VComponent;


	struct Vector3
	{
	public:
		Vector3();

		explicit Vector3(VComponent x);

		Vector3(VComponent x, VComponent y, VComponent z);

		// Get vector length, or magnitude.
		VComponent length() const;

		// Return normalized vector.
		Vector3 normalize() const;

		// Check for equality.
		bool operator==(const Vector3& other) const;

		// Check for inequality.
		bool operator!=(const Vector3& other) const;
		
		// Assignment operator.
		Vector3& operator=(const Vector3& other);

		// Return the negative of the vector.
		Vector3 operator-() const;

		// Arithmetic operations and the corresponding combined assignment operators.

		Vector3 operator+(const Vector3& other) const;

		Vector3& operator+=(const Vector3& other);

		Vector3 operator-(const Vector3& other) const;

		Vector3& operator-=(const Vector3& other);

		Vector3 operator*(VComponent val) const;

		Vector3& operator*=(VComponent val);

		// Throws: Exception
		Vector3 operator/(VComponent val) const;

		Vector3& operator/=(VComponent val);

	public:
		VComponent m_x;
		VComponent m_y;
		VComponent m_z;
	};
}
