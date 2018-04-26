#pragma once

#include "ImagePlane.h"


namespace GreenTopazTracerApp
{
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

		// Get raw image data (RGB format).
		// Parameters: size - number of elements.
		std::unique_ptr<COLORREF[]> getRawData(size_t& size) const
		{
			return m_imagePlane.getRawData(size);
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

		// Trace the specified ray.
		// Parameters: ray - ray to trace;
		//             steps - number of tracing steps already performed.
		Color traceRay(const Ray& ray, int steps) const;

		static DWORD WINAPI threadProc(LPVOID pArg);
		DWORD threadProc();

		// Get row and column of the next pixel.
		// Returns: true if there are more pixels, false once the image plane is completely processed.
		bool getRowAndColumn(LONG& row, LONG& column);

	public:
		std::vector<CHandle> m_threads;

	private:
		ImagePlane m_imagePlane;

		Scene m_scene;

		// Number of threads to perform ray tracing.
		const int ThreadCount;

		// Maximum number of steps for ray tracing.
		const int MaxTracingSteps;

		int m_horizontalResolution;
		int m_verticalResolution;

		long m_pixelCount;

		// Counter for the currently processed pixel. 
		__declspec(align(4)) volatile LONG m_currentPixel;

		// Current values of pixel row and column.
		__declspec(align(4)) volatile LONG m_row;
		__declspec(align(4)) volatile LONG m_column;
	};
}
