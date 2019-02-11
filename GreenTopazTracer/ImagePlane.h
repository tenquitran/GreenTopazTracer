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

		int getHorizontalResolution() const
		{
			return HorizontalRes;
		}

		int getVerticalResolution() const
		{
			return VerticalRes;
		}

		Color getPixelColor(int index) const;

		void setPixelColor(int index, const Color& clr);

		void setPixelColor(int row, int column, const Color& clr);

		// Prepare the image data for usage by the WIC image exporter.
		// Parameters: stride - stride value for the resulting image;
		//             bufferSize - size of the returned data buffer, in bytes.
		// Returns: the image data buffer.
		std::unique_ptr<BYTE[]> exportForWicImageProcessor(UINT& stride, UINT& bufferSize) const;

		// Get raw image data (BGR format).
		// Parameters: size - number of elements.
		std::unique_ptr<COLORREF[]> getRawDataBGR(size_t& size) const;

	private:
		ImagePlane(const ImagePlane&) = delete;
		ImagePlane& operator=(const ImagePlane&) = delete;

	public:
		// Horizontal resolution.
        const int HorizontalRes = {};

		// Vertical resolution.
        const int VerticalRes = {};

		// Size of one pixel.
        const VComponent PixelSize = { 1.0 };

	private:
		// Number of image plane elements.
        const int ElementCount = {};

		// Image plane elements.
        Color *m_ppPlane = { nullptr };

		// Lock for readers and writers.
		// Note that writers by themselves don't need it - they work with pixel indices.
		// It's reading that needs a lock.
		mutable CRITICAL_SECTION m_lock;

		// Number of the actually processed plane elements. Used for troubleshooting.
		volatile LONG m_processedElements;
	};
}
