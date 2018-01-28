#pragma once

#include "ImagePlane.h"


namespace GreenTopazTracerApp
{
	class GreenTopazTracer
	{
	public:
		void traceScene() const;

	private:
		ImagePlane m_imagePlane;
	};
}
