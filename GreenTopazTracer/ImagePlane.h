#pragma once


namespace GreenTopazTracerApp
{
	class ImagePlane
	{
	public:
		// Arguments: horizontalRes - horizontal resolution of the image plane;
		//            verticalRes   - vertical resolution of the image plane.
		// Throws: Exception, std::bad_alloc
		ImagePlane(int horizontalRes, int verticalRes);

		virtual ~ImagePlane();

		Color getPixelColor(int index) const;

		void setPixelColor(int index, const Color& clr);

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
	};
}
