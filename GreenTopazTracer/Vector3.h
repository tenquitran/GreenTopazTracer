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

	public:
		VComponent m_x;
		VComponent m_y;
		VComponent m_z;
	};
}
