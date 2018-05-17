#include "stdafx.h"
#include "ImagePlane.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


ImagePlane::ImagePlane(int horizontalRes, int verticalRes)
	: HorizontalRes(horizontalRes), VerticalRes(verticalRes), PixelSize(1.0), 
	  ElementCount(horizontalRes * verticalRes), m_ppPlane(nullptr)
{
	InterlockedExchange(&m_processedElements, 0L);

	InitializeCriticalSection(&m_lock);

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

	DeleteCriticalSection(&m_lock);
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

	EnterCriticalSection(&m_lock);

	m_ppPlane[index] = clr;

	LeaveCriticalSection(&m_lock);

	InterlockedIncrement(&m_processedElements);
}

void ImagePlane::setPixelColor(int row, int column, const Color& clr)
{
	// TODO: temp
#if 0//_DEBUG
	CAtlString msg;
	msg.Format(L"row: %d, column: %d\n", row, column);
	OutputDebugStringW(msg);
#endif

	int index = row * HorizontalRes + column;

	if (   index < 0
		|| index >= ElementCount)
	{
		assert(false); return;
	}

	EnterCriticalSection(&m_lock);

	m_ppPlane[index] = clr;

	LeaveCriticalSection(&m_lock);

	InterlockedIncrement(&m_processedElements);
}

std::unique_ptr<BYTE[]> ImagePlane::exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const
{
	std::wcout << TIME_STR() << "ImagePlane: " << m_processedElements 
		<< " of " << (HorizontalRes * VerticalRes) << " elements processed" << std::endl;

	stride = (HorizontalRes * 24 + 7) / 8;

	bufferSize = VerticalRes * stride;

	std::unique_ptr<BYTE[]> spBuffer = std::make_unique<BYTE[]>(bufferSize);

	UINT colorOffset = {};

	EnterCriticalSection(&m_lock);

	for (int i = 0; i < ElementCount; ++i)
	{
		COLORREF rgb = getPixelColor(i).toRGB();

		// Buffer should be in the BGR format.
		spBuffer[colorOffset++] = GetBValue(rgb);
		spBuffer[colorOffset++] = GetGValue(rgb);
		spBuffer[colorOffset++] = GetRValue(rgb);
	}

	LeaveCriticalSection(&m_lock);

	return spBuffer;
}

std::unique_ptr<COLORREF[]> ImagePlane::getRawDataBGR(size_t& size) const
{
	size = ElementCount;

	std::unique_ptr<COLORREF[]> spBuffer = std::make_unique<COLORREF[]>(ElementCount);

	EnterCriticalSection(&m_lock);

	for (int i = 0; i < ElementCount; ++i)
	{
		spBuffer[i] = getPixelColor(i).toBGR();
	}

	LeaveCriticalSection(&m_lock);

	return spBuffer;
}
