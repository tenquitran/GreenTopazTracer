#include "stdafx.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


GreenTopazTracer::GreenTopazTracer(int imageWidth, int imageHeight, int threadCount, int maxTracingSteps)
	: m_imagePlane(imageWidth, imageHeight), 
	  ThreadCount(threadCount), MaxTracingSteps(maxTracingSteps),
	  m_horizontalResolution{}, m_verticalResolution{}, m_pixelCount{}
{
	InterlockedExchange(&m_currentPixel, 0L);

	// Note: the column value will be incremented right away, so it should be (-1).
	InterlockedExchange(&m_row, 0L);
	InterlockedExchange(&m_column, -1L);

	m_horizontalResolution = m_imagePlane.HorizontalRes;
	m_verticalResolution   = m_imagePlane.VerticalRes;

	m_pixelCount = m_horizontalResolution * m_verticalResolution;

	// TODO: temp
#if 0
	tmpFunc();
#endif
}

GreenTopazTracer::~GreenTopazTracer()
{
}

bool GreenTopazTracer::getRowAndColumn(LONG& row, LONG& column)
{
#if 1
	// Worse.

	column = InterlockedIncrement(&m_column);

	if (column >= m_horizontalResolution)
	{
		InterlockedExchange(&m_column, 0L);

		row = InterlockedIncrement(&m_row);
		if (row >= m_verticalResolution)
		{
			return false;
		}
	}

	return true;
#else
	// Bad.

	row    = InterlockedExchange(&m_row, m_row);
	column = InterlockedExchange(&m_column, m_column);

	if (InterlockedIncrement(&m_column) >= m_horizontalResolution)
	{
		InterlockedExchange(&m_column, 0L);
		
		if (InterlockedIncrement(&m_row) >= m_verticalResolution)
		{
			return false;
		}
	}

	return true;
#endif
}

DWORD WINAPI GreenTopazTracer::threadProc(LPVOID pArg)
{
	GreenTopazTracer *pTracer = (GreenTopazTracer *)pArg;
	if (!pTracer)
	{
		assert(false); return 1;
	}

	return (pTracer->threadProc());
}

DWORD GreenTopazTracer::threadProc()
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

	// Z coordinate of the view plane.
	const VComponent ViewZ = 100.0;

	const VComponent PixelSize = m_imagePlane.PixelSize;

	const int SampleCount = 9;    // TODO: hard-coded

	Sampler sampler(SampleCount);

	LONG row = {}, column = {};

	// TODO: remove
	bool toContinue = true;

	do
	{
#if 1
		LONG previousCounter = InterlockedIncrement(&m_currentPixel);
		if (previousCounter >= m_pixelCount)
		{
			return 0;
		}
#endif

#if 1
		// Get row and column indices.

		column = InterlockedIncrement(&m_column);

		if (column >= m_horizontalResolution)
		{
			InterlockedExchange(&m_column, 0L);
			column = 0;

			row = InterlockedIncrement(&m_row);
			if (row >= m_verticalResolution)
			{
				return 0;    // finished tracing
			}
		}

		row = InterlockedExchange(&m_row, m_row);

		// TODO: temp
#if _DEBUG
		if (   0 == row
			&& 1 == column)
		{
			static int counter = 0;
			if (counter > 0)
			{
				int tmp = 1;
			}
			++counter;
		}
#endif

#else
		toContinue = getRowAndColumn(row, column);
		if (!toContinue)
		{
			break;
		}
#endif

		VComponent x = PixelSize * (column - 0.5 * (m_horizontalResolution - 1.0));
		VComponent y = PixelSize * (row    - 0.5 * (m_verticalResolution   - 1.0));

#if 0
		// TODO: temp
		m_imagePlane.setPixelColor(row, column, Color(1.0, 0.0, 0.0));
#else
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
		//m_imagePlane.setPixelColor(previousCounter++, clr / SampleCount);
#endif
		
	} while (toContinue);

	return 0;
}

void GreenTopazTracer::traceScene()
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

#if 1    // use multithreading and multisampling
	m_threads.resize(ThreadCount);

	for (int i = 0; i < ThreadCount; ++i)
	{
		m_threads[i].Attach(CreateThread(nullptr, 0, threadProc, this, CREATE_SUSPENDED, nullptr));
		if (!m_threads[i])
		{
			std::wcerr << __FUNCTIONW__ << L": CreateThread() failed: " << GetLastError() << '\n';
			assert(false); return;
		}
	}

	for (int i = 0; i < ThreadCount; ++i)
	{
		if ((DWORD)-1 == ResumeThread(m_threads[i]))
		{
			std::wcerr << __FUNCTIONW__ << L": ResumeThread() failed: " << GetLastError() << '\n';
			assert(false); return;
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
		assert(false);
	}

	int tmp = 1;
#endif
}

Color GreenTopazTracer::traceRay(const Ray& ray, int steps) const
{
	if (steps > MaxTracingSteps)
	{
		return Color() /*m_backgroundColor*/;
	}
#if 0
	else if (ray.isIntensityTooLow())
	{
		return Color();
	}
#endif

	HitInfo hit = m_scene.findNearestHit(ray);

	if (!hit.isValid())
	{
		return (/*ray.m_intensity * */ m_scene.getBackgroundColor());    // no intersection
	}

	// TODO: temp, simplified.
	return (hit.m_pHit->getColor());
	
	// Code from the older version of the ray tracer.
#if 0
	//glm::dvec3 intersection;    // distance
	//Intersectable * const pIntersectedObj = m_scene.findIntersection(ray, intersection);

	// Intersection with a scene object.
	// Instead of checking each particular type (sphere, triangle, etc.), we're using HasMaterial mix-in.
	HasMaterial *pHasMaterial = dynamic_cast<HasMaterial *>(pIntersectedObj);
	if (!pHasMaterial)
	{
		// Light sources have no material.
		LightSource *pIsLight = dynamic_cast<LightSource *>(pIntersectedObj);
		if (!pIsLight)
		{
			assert(false); return m_scene.getBackgroundColor();    // serious error
		}
		else
		{
			// TODO: calculate the color of light. Probably needs an improvement.
			return (pIsLight->m_color * pIsLight->m_brightness)/*.clamp()*/;
		}
	}

	Material material = pHasMaterial->getMaterial();

	// Note that these calculations cannot be performed by scene objects - they don't know about other objects or light sources.

	// Normal at the intersection point.
	glm::dvec3 normal = pIntersectedObj->getNormal(intersection);

	Color phong = m_scene.calculatePhongColor(material, intersection, ray.m_direction, normal) * ray.m_intensity;

	Color reflected;
	Color refracted;

	if (   material.isReflective()
		|| material.isTransparent())
	{
		double srcRefraction = m_scene.getRefractionIndex();
		double destRefraction = material.m_refractionIndex;

		// Check if the ray and normal are pointing more or less in the same direction - i.e. we are inside an object.
		if (glm::dot(ray.m_direction, normal) > 0)
		{
			normal = -normal;
			srcRefraction = material.m_refractionIndex;
			destRefraction = m_scene.getRefractionIndex();

			// TODO: temp
			if (EIntersectableType::Sphere == pIntersectedObj->getIntersectableType())
			{
				int tmp = 1;
			}
			if (material.isTransparent())
			{
				int tmp = 1;
			}
		}

		glm::dvec3 reflectedDir = calculateReflectedDirection(ray.m_direction, normal);

		if (material.isReflective())
		{
			Color reflectedColor = traceRay(Ray(intersection + reflectedDir * glm::epsilon<double>(), reflectedDir, ray.m_intensity), steps + 1);

			reflected = (reflectedColor * material.m_reflectivity * material.m_diffuseColor * ray.m_intensity).clamp();
		}

		if (material.isTransparent())
		{
			glm::dvec3 refractedDir = calculateRefractedDirection(ray.m_direction, normal, srcRefraction, destRefraction);

			// TODO: decrease ray intensity

			refracted = traceRay(Ray(intersection, refractedDir, ray.m_intensity), steps + 1);
		}
	}

	//Cres = (1 - T) * (C + R * Cr) + T * Ct

#if 1    // with refraction
	return (material.m_opacity * (phong + reflected) + refracted * (1.0 - material.m_opacity)).clamp();
	//return (material.m_opacity * (phong + material.m_reflectivity * reflected) + transparent).clamp();
#else
	// without refraction
	return (phong + reflected).clamp();
#endif

	//return (lambertianColor(material, intersection, normal) /*+ reflected*/ /* + refracted*/);    // TODO: uncomment
	//return phong.clamp();

#endif
}

#if 0
void GreenTopazTracer::tmpFunc()
{
	LONG row = {}, column = {};

	bool toContinue = true;

	do
	{
		LONG previousCounter = InterlockedIncrement(&m_currentPixel);
		if (previousCounter >= m_pixelCount)
		{
			return;
		}

		toContinue = getRowAndColumn(row, column);
		if (!toContinue)
		{
			break;
		}

		std::wcerr << row << ", " << column << '\n';

	} while (toContinue);

	std::wcerr << L"----------------------------------------------\n";
}
#endif
