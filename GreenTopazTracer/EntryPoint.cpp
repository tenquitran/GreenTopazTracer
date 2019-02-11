#include "stdafx.h"
#include "MainWindow.h"
#include "GreenTopazTracer.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Redirect output from std::cout and std::cerr to the log file.
	std::wofstream out("log.txt");
	std::wcout.rdbuf(out.rdbuf());
	std::wcerr.rdbuf(out.rdbuf());

	int ret = {};

	try
	{
		const int ImageWidth  = 800;
		const int ImageHeight = 600;

#if 0
		// TODO: temp
		DWORD tick1 = GetTickCount();

		// TODO: temp. Testing the tracer code.
		// Later we'll start tracing on receiving some window message, etc.
		GreenTopazTracer tracer(ImageWidth, ImageHeight);
		tracer.traceScene();

		// TODO: temp. Testing exporting of the resulting image.
		UINT stride = {};
		UINT bufferSize = {};
		std::unique_ptr<BYTE[]> spImageData = tracer.exportForWicImageProcessor(stride, bufferSize);
		ImageProcessor imgProcessor;
		const std::wstring filePath = L"file1.png";
		bool resExport = imgProcessor.saveAsPng(filePath, ImageWidth, ImageHeight, spImageData, stride, bufferSize);

		// TODO: temp
		DWORD tick2 = GetTickCount() - tick1;
#endif

        // Check out suitable number of threads (by default, 4).

        unsigned int threadCount = std::thread::hardware_concurrency();

        if (0 == threadCount)
        {
            threadCount = 4;
        }

        MainWindow mainWindow(hInstance, nCmdShow, ImageWidth, ImageHeight, threadCount);

		//imagePlane.setPixelColor(0, 0, Color(1, 1, 1));
		//imagePlane.setPixelColor(0, 1, Color(2, 2, 2));

		ret = mainWindow.runMessageLoop();
	}
	catch (const Exception& ex)
	{
		std::wcerr << ex.message() << std::endl;
        ATLASSERT(FALSE);
	}
	catch (const std::bad_alloc&)
	{
		std::wcerr << L"memalloc failure\n";
        ATLASSERT(FALSE);
	}

	return ret;
}
