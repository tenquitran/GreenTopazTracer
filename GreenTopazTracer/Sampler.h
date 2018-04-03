#pragma once


namespace GreenTopazTracerApp
{
	// Performs multisampling.
	// Suppose pixels are counted left to right and top to bottom; the origin is (-0.5, 0.5)
	class Sampler
	{
	public:
		Sampler(int horizontalRes, int verticalRes, int sampleCount);

		virtual ~Sampler();

		// TODO: remove
		// Get samples for the next pixel using the jittered sampling method.
		std::vector< std::pair<VComponent, VComponent> > getSamples_Jittered1();

		// Get samples for the next pixel using the jittered sampling method.
		std::vector< std::pair<VComponent, VComponent> > getSamples_Jittered(VComponent pixelX, VComponent pixelY);

	private:
		Sampler(const Sampler&) = delete;
		Sampler& operator=(const Sampler&) = delete;

	private:
		const int HorizontalRes;
		const int VerticalRes;

		const int SampleCount;

		int m_xCounter;
		int m_yCounter;

		std::mt19937 m_randomEngine;
	};
}
