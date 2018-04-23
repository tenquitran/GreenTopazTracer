#include "stdafx.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


GreenTopazTracer::GreenTopazTracer(int imageWidth, int imageHeight)
	: m_imagePlane(imageWidth, imageHeight), m_maxTracingSteps(10),
	  m_horizontalResolution{}, m_verticalResolution{}, m_pixelCount{}
{
	InterlockedExchange(&m_currentPixel, 0L);
	//m_currentPixel.store(0L);

	m_horizontalResolution = m_imagePlane.HorizontalRes;
	m_verticalResolution   = m_imagePlane.VerticalRes;

	m_pixelCount = m_horizontalResolution * m_verticalResolution;
}

GreenTopazTracer::~GreenTopazTracer()
{
}

// TODO: use multithreading.
#if 1
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

	const int SampleCount = 9;    // TODO: hard-coded

	Sampler sampler(SampleCount);

	while (true)
	{
		LONG previousCounter = InterlockedIncrement(&m_currentPixel);
		if (previousCounter >= m_pixelCount)
		{
			return 0;
		}

		std::pair<VComponent, VComponent> coords = m_pixelCoords[previousCounter];

#if 1
		//VComponent x = PixelSize * (col - 0.5 * (m_horizontalResolution - 1.0));
		//VComponent y = PixelSize * (row - 0.5 * (m_verticalResolution - 1.0));

		// Generate samples inside the pixel and trace rays from these samples.

		std::vector<Pixel> samples = sampler.getSamples_Jittered(coords.first, coords.second);

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

		m_imagePlane.setPixelColor(previousCounter++, clr / SampleCount);
#endif
	}
}
#endif 	  // TODO: use multithreading.

void GreenTopazTracer::traceScene()
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

	// Z coordinate of the view plane.
	const VComponent ViewZ = 100.0;

	//const int HorizRes = m_imagePlane.HorizontalRes;
	//const int VertRes = m_imagePlane.VerticalRes;

	const VComponent PixelSize = m_imagePlane.PixelSize;

	// TODO: use multithreading.
#if 1
	const int ThreadCount = 4;    // TODO: hard-coded

	CHandle threads[ThreadCount];
	HANDLE threadHandles[ThreadCount];

	for (int i = 0; i < ThreadCount; ++i)
	{
		threads[i].Attach(CreateThread(nullptr, 0, threadProc, this, CREATE_SUSPENDED, nullptr));
		if (!threads[i])
		{
			// TODO: error
			assert(false); return;
		}

		threadHandles[i] = threads[i].m_h;
	}
#endif

	m_pixelCoords.reserve(m_pixelCount);

#if 1
	// Using multisampling.

	//const int PixelCount = m_horizontalResolution * m_verticalResolution;

	const int SampleCount = 9;    // TODO: hard-coded

	Sampler sampler(SampleCount);

	int index = {};    // index of the image plane element

	for (int row = 0; row < m_verticalResolution; ++row)
	{
		for (int col = 0; col < m_horizontalResolution; ++col)
		{
#if 1    // use multithreading
			VComponent x = PixelSize * (col - 0.5 * (m_horizontalResolution - 1.0));
			VComponent y = PixelSize * (row - 0.5 * (m_verticalResolution   - 1.0));

			m_pixelCoords.push_back(std::pair<VComponent, VComponent>(x, y));
#else
			VComponent x = PixelSize * (col - 0.5 * (m_horizontalResolution - 1.0));
			VComponent y = PixelSize * (row - 0.5 * (m_verticalResolution   - 1.0));

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

			m_imagePlane.setPixelColor(index++, clr / SampleCount);
#endif
		}
	}

	// TODO: use multithreading.
#if 1
	for (int i = 0; i < ThreadCount; ++i)
	{
		if ((DWORD)-1 == ResumeThread(threads[i]))
		{
			// TODO: error
			assert(false); return;
		}
	}

	DWORD waitRes = WaitForMultipleObjects(_countof(threadHandles), threadHandles, TRUE, 60000);
	switch (waitRes)
	{
	case WAIT_TIMEOUT:
		std::cout << "Timeout" << std::endl;
		break;
	case WAIT_FAILED:
		std::cout << "Error" << std::endl;
		break;
		}
#endif

#else
	// TODO: don't delete. The edges are somewhat more accurate than with one-pixel jittered sampling.

	// Suppose the origin of the image plane is at its lower left corner.
	// Trace rays according to rows and columns of the image plane.

	int index = {};    // index of the image plane element

	// TODO: temp
	//VComponent x = {};
	//VComponent y = {};

	for (int row = 0; row < VertRes; ++row)
	{
		for (int col = 0; col < HorizRes; ++col)
		{
			VComponent x = PixelSize * (col - 0.5 * (HorizRes - 1.0));
			VComponent y = PixelSize * (row - 0.5 * (VertRes - 1.0));

			Vector3 origin = Vector3(x, y, ViewZ);

			Ray ray(origin, RayDirection);

			Color pixelColor = traceRay(ray, 0);

			m_imagePlane.setPixelColor(index++, pixelColor);
		}
	}
#endif

	int tmp = 1;
}

Color GreenTopazTracer::traceRay(const Ray& ray, int steps) const
{
	if (steps > m_maxTracingSteps)
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
