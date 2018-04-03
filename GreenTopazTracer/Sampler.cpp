#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Sampler::Sampler(int sampleCount)
	: SampleCount(sampleCount), m_randomEngine(std::random_device{}())
{
}

Sampler::~Sampler()
{
}

std::vector<Pixel> Sampler::getSamples_Jittered(VComponent pixelX, VComponent pixelY)
{
	std::vector<Pixel> samples;
	samples.reserve(SampleCount);

	// Determine the edges of the current pixel.

	VComponent xMin = pixelX - 0.5f;
	VComponent yMin = pixelY - 0.5f;

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

		samples.push_back(Pixel(xDist(m_randomEngine), yDist(m_randomEngine)));
	}

	return samples;
}
