#pragma once


namespace GreenTopazTracerApp
{
	class ImagePlane
	{
	public:
		// Parameters: horizontalRes - horizontal resolution of the image plane;
		//             verticalRes   - vertical resolution of the image plane.
		// Throws: Exception, std::bad_alloc
		ImagePlane(int horizontalRes, int verticalRes);

		virtual ~ImagePlane();

		Color getPixelColor(int index) const;

		void setPixelColor(int index, const Color& clr);

		// Prepare the image data for usage by the WIC image exporter.
		// Parameters: stride - stride value for the resulting image;
		//             bufferSize - size of the returned data buffer, in bytes.
		// Returns: the image data buffer.
		std::unique_ptr<BYTE[]> exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const;

	private:
		ImagePlane(const ImagePlane&) = delete;
		ImagePlane& operator=(const ImagePlane&) = delete;

	public:
		// Horizontal resolution.
		const int HorizontalRes;

		// Vertical resolution.
		const int VerticalRes;

		// Size of one pixel.
		const VComponent PixelSize;

	private:
		// Number of image plane elements.
		const int ElementCount;

		// Image plane elements.
		Color *m_ppPlane;

#if 0
		// Copy of the image plane data to work with the WIC image exporter. Uses the BGR format.
		std::unique_ptr<BYTE[]> m_spBufferForWicExporter;
#endif
	};
}
