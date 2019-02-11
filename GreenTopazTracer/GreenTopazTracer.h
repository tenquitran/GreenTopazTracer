#pragma once

#include "ImagePlane.h"


namespace GreenTopazTracerApp
{
	// The ray tracer.
	class GreenTopazTracer
	{
	public:
		// Parameters: imageWidth  - width of the image to trace (in pixels);
		//             imageHeight - height of the image to trace (in pixels);
		//             threadCount - number of threads to perform ray tracing;
		//             maxTracingSteps - maximum number of steps for ray tracing.
		// Throws: Exception, std::bad_alloc
		GreenTopazTracer(int imageWidth, int imageHeight, int threadCount, int maxTracingSteps);

		virtual ~GreenTopazTracer();

		// Start ray tracing the scene.
		void traceScene();

		// Prepare the image data for usage by the WIC image exporter.
		// Parameters: stride - stride value for the resulting image;
		//             bufferSize - size of the returned data buffer, in bytes.
		// Returns: the image data buffer.
		std::unique_ptr<BYTE[]> exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const
		{
			return m_imagePlane.exportForWicImageProcessor(stride, bufferSize);
		}

		// Get raw image data (BGR format).
		// Parameters: size - number of elements.
		std::unique_ptr<COLORREF[]> getRawDataBGR(size_t& size) const
		{
			return m_imagePlane.getRawDataBGR(size);
		}

		int getHorizontalResolution() const
		{
			return m_imagePlane.getHorizontalResolution();
		}

		int getVerticalResolution() const
		{
			return m_imagePlane.getVerticalResolution();
		}

		const int getThreadCount() const
		{
			return ThreadCount;
		}

	private:
		GreenTopazTracer(const GreenTopazTracer&) = delete;
		GreenTopazTracer& operator=(const GreenTopazTracer&) = delete;

		static DWORD WINAPI threadProc(LPVOID pArg);
		DWORD threadProc();

		// Trace the specified ray.
		// Parameters: ray - ray to trace;
		//             steps - number of tracing steps already performed.
		Color traceRay(const Ray& ray, int steps) const;

	public:
		std::vector<CHandle> m_threads;

	private:
        const int HorizontalResolution = {};
        const int VerticalResolution   = {};

		// Number of pixels in the image.
        const long PixelCount = {};

		// Number of threads to perform ray tracing.
        const int ThreadCount = {};

		// Maximum number of steps for ray tracing.
        const int MaxTracingSteps = {};

		ImagePlane m_imagePlane;

		Scene m_scene;

		// Used to get the next pixel to process.
		PixelCounter m_pixelCounter;
	};
}
