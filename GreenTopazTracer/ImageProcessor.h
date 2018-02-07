#pragma once


namespace GreenTopazTracerApp
{
	// Image processor using WIC (Windows Imaging Component). 
	class ImageProcessor
	{
	public:
		// Throws: Exception
		ImageProcessor();

		virtual ~ImageProcessor();

		// Save image file in the PNG format.
		// Parameters: filePath - file name or relative path (with extension);
		//             fileWidth - file width in pixels;
		//             fileHeight - file height in pixels;
		//             spData - data buffer to save (BGR color);
		//             stride - image stride;
		//             bufferSize - data buffer size in bytes.
		bool saveAsPng(const std::wstring& filePath, UINT fileWidth, UINT fileHeight, 
			const std::unique_ptr<BYTE[]>& spData, UINT stride, UINT bufferSize);

		// TODO: implement only if required
#if 0
		// Load image file.
		// Parameters: filePath - file name or relative path.
		Image load(const std::string& filePath);
#endif

	private:
		// WIC (Windows Imaging Component) factory.
		CComPtr<IWICImagingFactory> m_spFactory;
	};
}
