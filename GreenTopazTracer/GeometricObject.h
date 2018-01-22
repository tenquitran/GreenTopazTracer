#pragma once


namespace GreenTopazTracerApp
{
	class GeometricObject
	{
	public:
		GeometricObject();

		virtual ~GeometricObject();

	protected:
		Vector3 m_center;
	};
}
