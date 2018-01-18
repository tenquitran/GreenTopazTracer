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

	// TODO: temp
#if 1
	Vector3 v(2, 4, -8);
	Color clr(0.2, 0.5, 0.5);

	VComponent ln = v.length();
	Vector3 vn = v.normalize();

	Vector3 v2 = v / 0;

	v /= 2;
	int tmp = 1;
#endif

	try
	{
		MainWindow mainWindow(hInstance, nCmdShow);

		ret = mainWindow.runMessageLoop();
	}
	catch (const Exception& ex)
	{
		std::wcerr << ex.message() << std::endl;
		assert(false);
	}
	catch (const std::bad_alloc&)
	{
		std::wcerr << L"memalloc failure\n";
		assert(false);
	}

	return ret;
}
