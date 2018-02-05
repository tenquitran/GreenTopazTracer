#include "stdafx.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


GreenTopazTracer::GreenTopazTracer(int imageWidth, int imageHeight)
	: m_imagePlane(imageWidth, imageHeight)
{
}

GreenTopazTracer::~GreenTopazTracer()
{
}

void GreenTopazTracer::traceScene() const
{
	const Vector3 RayDirection(0.0, 0.0, -1.0);

	// Z coordinate of the view plane.
	const VComponent ViewZ = 100.0;

	const int HorizRes = m_imagePlane.HorizontalRes;
	const int VertRes  = m_imagePlane.VerticalRes;

	const VComponent PixelSize = m_imagePlane.PixelSize;

	// Suppose the origin of the image plane is at its lower left corner.
	// Trace rays according to rows and columns of the image plane.

	for (int row = 0; row < VertRes; ++row)
	{
		for (int col = 0; col < HorizRes; ++col)
		{
			VComponent x = PixelSize * (col - 0.5 * (HorizRes - 1.0));
			VComponent y = PixelSize * (row - 0.5 * (VertRes - 1.0));

			Vector3 origin = Vector3(x, y, ViewZ);

			Ray ray(origin, RayDirection);

			//Color pixelColor = traceRay(ray);
		}
	}
}
