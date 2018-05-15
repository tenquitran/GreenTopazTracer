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

		// Trace the specified ray.
		// Parameters: ray - ray to trace;
		//             steps - number of tracing steps already performed.
		Color traceRay(const Ray& ray, int steps) const;

		static DWORD WINAPI threadProc(LPVOID pArg);
		DWORD threadProc();

		// Get row and column of the next pixel.
		// Parameters: row, column - valid only if the function returns true.
		// Returns: true if not all image plane pixels were processed yet, false otherwise.
		bool getRowAndColumn(LONG& row, LONG& column);

#if 0
		// TODO: temp, searching for bugs in the multithreaded code.
		void tmpFunc();
#endif

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

		// TODO: remove but check out that ImagePlane is properly processed in the end.
#if 1
		// Counter for the currently processed pixel. 
		__declspec(align(8)) volatile LONG m_currentPixel;
#endif

		// Current values of pixel row and column.
		__declspec(align(8)) volatile LONG m_row;
		__declspec(align(8)) volatile LONG m_column;
	};
}
