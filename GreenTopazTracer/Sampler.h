#pragma once


namespace GreenTopazTracerApp
{
	// Performs multisampling.
	// Suppose pixels are counted left to right and top to bottom; the origin is (-0.5, 0.5)
	class Sampler
	{
	public:
		explicit Sampler(int sampleCount);

		virtual ~Sampler();

		// Get samples for the pixel using the jittered sampling method.
		// Parameters: pixelX, pixelY - coordinates of the pixel center.
		std::vector<Pixel> getSamples_Jittered(VComponent pixelX, VComponent pixelY);

	private:
		Sampler(const Sampler&) = delete;
		Sampler& operator=(const Sampler&) = delete;

	private:
        const int SampleCount = {};

		std::mt19937 m_randomEngine;
	};
}
