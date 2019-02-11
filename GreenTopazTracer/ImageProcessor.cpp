#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


ImageProcessor::ImageProcessor()
{
	HRESULT hr = CoInitialize(nullptr);    // initialize COM
	if (FAILED(hr))
	{
		throw EXCEPTION_FMT(L"CoInitialize() failed: 0x%x (%s)", hr, _com_error(hr).ErrorMessage());
	}

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_spFactory));
	if (FAILED(hr))
	{
		throw EXCEPTION_FMT(L"Failed to create imaging factory: 0x%x (%s)", hr, _com_error(hr).ErrorMessage());
	}
}

ImageProcessor::~ImageProcessor()
{
	CoUninitialize();
}

bool ImageProcessor::saveAsPng(const std::wstring& filePath, UINT width, UINT height, 
	const std::unique_ptr<BYTE[]>& spData, UINT stride, UINT bufferSize)
{
	if (filePath.empty())
	{
		std::wcerr << L"Empty file path\n";
        ATLASSERT(FALSE); return false;
	}
	else if (width < 0 || height < 0)
	{
		std::wcerr << L"Invalid image dimensions\n";
        ATLASSERT(FALSE); return false;
	}
	else if (!spData)
	{
		std::wcerr << L"No data to write\n";
        ATLASSERT(FALSE); return false;
	}

	CComPtr<IWICStream> spStream;

	HRESULT hr = m_spFactory->CreateStream(&spStream);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to create stream: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	hr = spStream->InitializeFromFilename(filePath.c_str(), GENERIC_WRITE);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to initialize stream (file " 
			<< filePath.c_str() << "): " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	CComPtr<IWICBitmapEncoder> spEncoder;

	hr = m_spFactory->CreateEncoder(GUID_ContainerFormatPng, nullptr, &spEncoder);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to create PNG encoder: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	hr = spEncoder->Initialize(spStream, WICBitmapEncoderNoCache);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to initialize PNG encoder: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	CComPtr<IWICBitmapFrameEncode> spBitmapFrame;
	CComPtr<IPropertyBag2> spPropertyBag;

	hr = spEncoder->CreateNewFrame(&spBitmapFrame, &spPropertyBag);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to create frame: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	// Even if we don't specify any properties, the property bag seems to be required.
	hr = spBitmapFrame->Initialize(spPropertyBag);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to initialize property bag: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	hr = spBitmapFrame->SetSize(width, height);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to set bitmap frame size: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	WICPixelFormatGUID formatGUID = GUID_WICPixelFormat24bppBGR;
	
	hr = spBitmapFrame->SetPixelFormat(&formatGUID);
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to set pixel format: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	// We are expecting to use the specified format (the data are arranged accordingly).
	hr = IsEqualGUID(formatGUID, GUID_WICPixelFormat24bppBGR) ? S_OK : E_FAIL;
	if (FAILED(hr))
	{
		std::wcerr << L"Unexpected pixel format: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

#if 0
	const UINT stride = (width * 24 + 7) / 8;

	const UINT bufferSize = height * stride;

	std::unique_ptr<BYTE[]> spBuffer;

	try
	{
		spBuffer = std::make_unique<BYTE[]>(bufferSize);

		for (UINT i = 0; i < bufferSize; i += 3)
		{
			// Blue color (BGR format).
			spBuffer[i] = 255;
			spBuffer[i + 1] = 128;
			spBuffer[i + 2] = 0;
		}
	}
	catch (const std::bad_alloc&)
	{
		logMessage(L"Memalloc failure (%u bytes)", bufferSize);
		return false;
	}
#endif

	hr = spBitmapFrame->WritePixels(height, stride, bufferSize, spData.get());
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to write pixels: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	hr = spBitmapFrame->Commit();
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to commit bitmap frame: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	hr = spEncoder->Commit();
	if (FAILED(hr))
	{
		std::wcerr << L"Failed to commit bitmap encoder: " << std::hex << hr << " (" << _com_error(hr).ErrorMessage() << ")\n";
        ATLASSERT(FALSE); return false;
	}

	return true;
}
