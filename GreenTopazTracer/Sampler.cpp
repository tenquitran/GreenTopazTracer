#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Sampler::Sampler(int horizontalRes, int verticalRes, int sampleCount)
	: HorizontalRes(horizontalRes), VerticalRes(verticalRes), SampleCount(sampleCount), 
	  m_xCounter{}, m_yCounter{}, m_randomEngine(std::random_device{}())
{
}

Sampler::~Sampler()
{
}

std::vector< std::pair<VComponent, VComponent> > Sampler::getSamples_Jittered()
{
	std::vector< std::pair<VComponent, VComponent> > samples;
	samples.reserve(SampleCount);

	// Determine the edges of the current pixel.

	VComponent xMin = m_xCounter - 0.5f;
	//VComponent xMax = m_xCounter + 0.5f;

	VComponent yMin = m_yCounter - 0.5f;
	//VComponent yMax = m_yCounter + 0.5f;

	// Split the pixel into (number of samples) bins organized in a 2D grid.

	const int GridSide = static_cast<int>(sqrt(SampleCount));

	// The size of the pixel is one.
	const VComponent BinWidth  = 1.0f / GridSide;
	const VComponent BinHeight = 1.0f / GridSide;

	VComponent binLeft = xMin;    // left edge of the bin
	VComponent binTop  = yMin;    // top edge of the bin

	for (int i = 0; i < SampleCount; ++i)
	{
		// Create random number generators for the current bin.

		std::uniform_real_distribution<VComponent> xDist(binLeft, binLeft + BinWidth);

		std::uniform_real_distribution<VComponent> yDist(binTop, binTop + BinHeight);

		binLeft += BinWidth;

		if (0 == (i + 1) % GridSide)    // next row of the bins
		{
			binLeft = xMin;
			binTop += BinHeight;
		}

		// Randomly get the sample coordinates inside the bin.

		VComponent x = xDist(m_randomEngine);
		VComponent y = yDist(m_randomEngine);

		samples.push_back(std::pair<VComponent, VComponent>(x, y));
	}

	// Move to the next pixel.

	++m_xCounter;

	if (HorizontalRes - 1 == m_xCounter)
	{
		m_xCounter = 0;
		++m_yCounter;
	}

	return samples;
}
