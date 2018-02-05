#include "stdafx.h"
#include "ImagePlane.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


ImagePlane::ImagePlane(int horizontalRes, int verticalRes)
	: HorizontalRes(horizontalRes), VerticalRes(verticalRes), PixelSize(1.0), 
	  ElementCount(horizontalRes * verticalRes), m_ppPlane(nullptr)
{
	if (   HorizontalRes <= 0
		|| VerticalRes   <= 0)
	{
		assert(false); throw EXCEPTION_FMT(L"Invalid horizontal (%d) and/or vertical (%d) resolution", HorizontalRes, VerticalRes);
	}

	m_ppPlane = new Color[ElementCount];

	memset(m_ppPlane, 0, ElementCount * sizeof(Color));
}

ImagePlane::~ImagePlane()
{
	if (m_ppPlane)
	{
		delete[] m_ppPlane;
	}
}

Color ImagePlane::getPixelColor(int index) const
{
	if (   index < 0
		|| index >= ElementCount)
	{
		assert(false); return Color();
	}

	return m_ppPlane[index];
}

void ImagePlane::setPixelColor(int index, const Color& clr)
{
	if (   index < 0
		|| index >= ElementCount)
	{
		assert(false); return;
	}

	m_ppPlane[index] = clr;
}
