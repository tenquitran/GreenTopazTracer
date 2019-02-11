#include "stdafx.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


GreenTopazTracer::GreenTopazTracer(int imageWidth, int imageHeight, unsigned int threadCount, int maxTracingSteps)
	: HorizontalResolution(imageWidth), VerticalResolution(imageHeight), PixelCount(imageWidth * imageHeight),
	  ThreadCount(threadCount), MaxTracingSteps(maxTracingSteps),
	  m_imagePlane(imageWidth, imageHeight), 
	  m_scene(Color(0.0, 0.64, 0.91)),    // light blue background
	  m_pixelCounter(imageWidth, imageHeight)
{
}

GreenTopazTracer::~GreenTopazTracer()
{
}

DWORD WINAPI GreenTopazTracer::threadProc(LPVOID pArg)
{
	GreenTopazTracer *pTracer = (GreenTopazTracer *)pArg;
	if (!pTracer)
	{
        ATLASSERT(FALSE); return 1;
	}

	return (pTracer->threadProc());
}

DWORD GreenTopazTracer::threadProc()
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

	// Z coordinate of the view plane.
    const VComponent ViewZ = 500.0;
    //const VComponent ViewZ = 100.0;

	const VComponent PixelSize = m_imagePlane.PixelSize;

	const int SampleCount = 9;    // TODO: hard-coded

	Sampler sampler(SampleCount);

	int row = {}, column = {};

	do
	{
		// Get row and column indices.
		if (!m_pixelCounter.getNext(row, column))
		{
			return 0;
		}

		VComponent x = PixelSize * (column - 0.5 * (HorizontalResolution - 1.0));
		VComponent y = PixelSize * (row    - 0.5 * (VerticalResolution   - 1.0));

		// Generate samples inside the pixel and trace rays from these samples.

		std::vector<Pixel> samples = sampler.getSamples_Jittered(x, y);

		std::vector<Color> sampleColors;
		sampleColors.reserve(SampleCount);

		for (const auto& itr : samples)
		{
			Vector3 origin = Vector3(itr.first, itr.second, ViewZ);

			Ray ray(origin, RayDirection);

			Color color = traceRay(ray, 0);

			sampleColors.push_back(color);
		}

		// Average the sample colors.

		Color clr;

		for (const auto& itr : sampleColors)
		{
			clr += itr;
		}

		m_imagePlane.setPixelColor(row, column, clr / SampleCount);

	} while (true);

	return 0;
}

void GreenTopazTracer::traceScene()
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

#if 1    // use multithreading and multisampling
	m_threads.resize(ThreadCount);

    for (unsigned int i = {}; i < ThreadCount; ++i)
	{
		m_threads[i].Attach(CreateThread(nullptr, 0, threadProc, this, CREATE_SUSPENDED, nullptr));
		if (!m_threads[i])
		{
			std::wcerr << __FUNCTIONW__ << L": CreateThread() failed: " << GetLastError() << '\n';
            ATLASSERT(FALSE); return;
		}
	}

    for (unsigned int i = {}; i < ThreadCount; ++i)
	{
		if ((DWORD)-1 == ResumeThread(m_threads[i]))
		{
			std::wcerr << __FUNCTIONW__ << L": ResumeThread() failed: " << GetLastError() << '\n';
            ATLASSERT(FALSE); return;
		}
	}
#else
	// Basic version without multithreading and multisampling.
	// WARNING: don't remove; is useful as a reference and for bugfixing.

	// Z coordinate of the view plane.
	const VComponent ViewZ = 100.0;

	const VComponent PixelSize = m_imagePlane.PixelSize;

	int index = {};

	for (int row = 0; row < m_verticalResolution; ++row)
	{
		for (int col = 0; col < m_horizontalResolution; ++col)
		{
			VComponent x = PixelSize * (col - 0.5 * (m_horizontalResolution - 1.0));
			VComponent y = PixelSize * (row - 0.5 * (m_verticalResolution - 1.0));

			Vector3 origin = Vector3(x, y, ViewZ);

			Ray ray(origin, RayDirection);

			Color pixelColor = traceRay(ray, 0);

			m_imagePlane.setPixelColor(index++, pixelColor);
		}
	}

	// Export the resulting image.

	UINT stride = {};
	UINT bufferSize = {};

	std::unique_ptr<BYTE[]> spImageData = exportForWicImageProcessor(stride, bufferSize);

	ImageProcessor imgProcessor;

	const std::wstring fileName = L"file2.png";

	if (imgProcessor.saveAsPng(
			fileName, getHorizontalResolution(), getVerticalResolution(), spImageData, stride, bufferSize))
	{
		std::wcout << TIME_STR() << L"Ray traced image saved: \"" << fileName << "\"" << std::endl;
	}
	else
	{
		std::wcerr << TIME_STR() << L"Failed to save the ray traced image\n";
        ATLASSERT(FALSE);
	}

	int tmp = 1;
#endif
}

Color GreenTopazTracer::traceRay(const Ray& ray, int steps) const
{
	if (steps > MaxTracingSteps)
	{
		return Color();
	}

	HitInfo hit = m_scene.findNearestHit(ray);

	if (!hit.isValid())
	{
		return m_scene.getBackgroundColor();    // no intersection
	}

#if 0
	// TODO: temp, simplified.
	return (hit.m_pHit->getColor());
#else
	return m_scene.computeIllumination(hit, ray.m_direction);
#endif
}
