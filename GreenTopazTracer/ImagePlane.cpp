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

std::unique_ptr<BYTE[]> ImagePlane::exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const
{
	stride = (HorizontalRes * 24 + 7) / 8;

	bufferSize = VerticalRes * stride;

	std::unique_ptr<BYTE[]> spBuffer = std::make_unique<BYTE[]>(bufferSize);

	UINT colorOffset = {};

	for (int i = 0; i < ElementCount; ++i)
	{
		COLORREF rgb = getPixelColor(i).toRGB();

		// Buffer should be in the BGR format.
		spBuffer[colorOffset++] = GetBValue(rgb);
		spBuffer[colorOffset++] = GetGValue(rgb);
		spBuffer[colorOffset++] = GetRValue(rgb);
	}

	return spBuffer;
}
