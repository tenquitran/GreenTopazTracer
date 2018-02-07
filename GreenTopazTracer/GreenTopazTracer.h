#pragma once

#include "ImagePlane.h"


namespace GreenTopazTracerApp
{
	class GreenTopazTracer
	{
	public:
		// Parameters: imageWidth  - width of the image to trace (in pixels);
		//             imageHeight - height of the image to trace (in pixels).
		// Throws: Exception, std::bad_alloc
		GreenTopazTracer(int imageWidth, int imageHeight);

		virtual ~GreenTopazTracer();

		void traceScene();

		// Prepare the image data for usage by the WIC image exporter.
		// Parameters: stride - stride value for the resulting image;
		//             bufferSize - size of the returned data buffer, in bytes.
		// Returns: the image data buffer.
		std::unique_ptr<BYTE[]> exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const
		{
			return m_imagePlane.exportForWicImageProcessor(stride, bufferSize);
		}

	private:
		// Trace the specified ray.
		// Parameters: ray - ray to trace;
		//             steps - number of tracing steps already performed.
		Color traceRay(const Ray& ray, int steps) const;

	private:
		ImagePlane m_imagePlane;

		Scene m_scene;

		// Maximum number of steps for ray tracing. Note: can be changed by the user.
		int m_maxTracingSteps;
	};
}
