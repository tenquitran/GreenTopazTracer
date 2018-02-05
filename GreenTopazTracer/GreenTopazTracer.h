#pragma once

#include "ImagePlane.h"


namespace GreenTopazTracerApp
{
	class GreenTopazTracer
	{
	public:
		// Arguments: imageWidth  - width of the image to trace (in pixels);
		//            imageHeight - height of the image to trace (in pixels).
		// Throws: Exception, std::bad_alloc
		GreenTopazTracer(int imageWidth, int imageHeight);

		virtual ~GreenTopazTracer();

		void traceScene() const;

	private:
		ImagePlane m_imagePlane;

		Scene m_scene;
	};
}
