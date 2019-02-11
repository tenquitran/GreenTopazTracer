#include "stdafx.h"
#include "resource.h"
#include "MainWindow.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

// Timer to display ray tracing results.
#define IDT_TRACE_RESULT_TIMER   2010

//////////////////////////////////////////////////////////////////////////


MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow, int clientWidth, int clientHeight)
	: m_hAppInstance(hInstance), m_clientWidth(clientWidth), m_clientHeight(clientHeight),
	  m_tracer(clientWidth, clientHeight, 
	  4, 10)    // TODO: hard-coded
{
	// Initialize global strings.
	LoadString(m_hAppInstance, IDS_APP_TITLE, m_titleBarStr, MaxLoadString);
	LoadString(m_hAppInstance, IDC_GREENTOPAZTRACER, m_windowClassName, MaxLoadString);

	registerWndClass();

	// Perform application initialization.
	if (!initInstance(nCmdShow))
	{
		ATLASSERT(FALSE); throw EXCEPTION(L"initInstance() failed");
	}

	if (!SetTimer(m_hMainWindow, IDT_TRACE_RESULT_TIMER, 300, (TIMERPROC)nullptr))    // 500
	{
        ATLASSERT(FALSE); throw EXCEPTION_FMT(L"SetTimer() failed: %u", GetLastError());
	}
}

MainWindow::~MainWindow()
{
}

ATOM MainWindow::registerWndClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = mainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hAppInstance;
	wcex.hIcon = LoadIcon(m_hAppInstance, MAKEINTRESOURCE(IDI_GREENTOPAZTRACER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GREENTOPAZTRACER);
	wcex.lpszClassName = m_windowClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL MainWindow::initInstance(int nCmdShow)
{
	// Create the window with the client area of the specified size.

	const DWORD WindowStyle = WS_POPUPWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;

	RECT wndRect = { 0, 0, m_clientWidth, m_clientHeight };

	BOOL res = AdjustWindowRect(&wndRect, WindowStyle, TRUE);
	if (!res)
	{
		std::wcerr << TIME_STR() << L"AdjustWindowRect() failed: " << GetLastError() << std::endl;
		return FALSE;
	}

	// Pass pointer to this class instance in the last argument of CreateWindow().
	m_hMainWindow = CreateWindow(m_windowClassName, m_titleBarStr, WindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
		nullptr, nullptr, m_hAppInstance, this);
	if (!m_hMainWindow)
	{
		std::wcerr << TIME_STR() << L"CreateWindow() failed: " << GetLastError() << std::endl;
		return FALSE;
	}

	std::wcout << TIME_STR() << L"Created main window\n";

	ShowWindow(m_hMainWindow, nCmdShow);
	UpdateWindow(m_hMainWindow);

	return TRUE;
}

void MainWindow::exportImage()
{
	UINT stride = {};
	UINT bufferSize = {};

	std::unique_ptr<BYTE[]> spImageData = m_tracer.exportForWicImageProcessor(stride, bufferSize);

	ImageProcessor imgProcessor;

	const std::wstring fileName = L"file1.png";

	if (imgProcessor.saveAsPng(
			fileName, m_tracer.getHorizontalResolution(), m_tracer.getVerticalResolution(), spImageData, stride, bufferSize))
	{
		std::wcout << TIME_STR() << L"Ray traced image saved: \"" << fileName << "\"" << std::endl;
	}
	else
	{
		std::wcerr << TIME_STR() << L"Failed to save the ray traced image\n";
        ATLASSERT(FALSE);
	}
}

int MainWindow::runMessageLoop()
{
	HACCEL hAccelTable = LoadAccelerators(m_hAppInstance, MAKEINTRESOURCE(IDC_GREENTOPAZTRACER));

	bool rayTracingComplete = false;

	MSG msg = {};

	while (true)
	{
		if (    m_rayTracingStarted
			&& !rayTracingComplete)
		{
			// Wait for the ray tracing to complete.

			// NOTE: Wrong! While some threads exit, others may still have work to do.
			// Use some wait function in the tracer class?

			// We rely on the fact that if any thread exits, the ray tracing is finished.
			HANDLE hThread = m_tracer.m_threads[0];

			DWORD waitStatus = MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLEVENTS);

			switch (waitStatus)
			{
			case WAIT_OBJECT_0:        // ray tracing complete
				rayTracingComplete = true;

				std::wcout << TIME_STR() << L"Ray tracing complete. Exporting the resulting image..." << std::endl;

				exportImage();
				break;
			case WAIT_FAILED:
				std::wcerr << TIME_STR() << __FUNCTIONW__ << L": unexpected wait status: " << waitStatus << '\n';
                ATLASSERT(FALSE); break;
			default:    // window message arrived
				break;
			}
		}

		// Window message processing.
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				return (int)msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

LRESULT CALLBACK MainWindow::mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static MainWindow *pMainWnd = nullptr;

	switch (message)
	{
	case WM_CREATE:
		pMainWnd = (MainWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (!pMainWnd)
		{
			std::wcerr << TIME_STR() << L"WM_CREATE: main window pointer is NULL\n";
            ATLASSERT(FALSE);
		}
		else
		{
			std::wcout << TIME_STR() << L"Starting ray tracing..." << std::endl;

			pMainWnd->m_rayTracingStarted = true;

			pMainWnd->m_tracer.traceScene();
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(pMainWnd->m_hAppInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, aboutDlgProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TRACE_RESULT_TIMER:
			{
				DWORD tick1 = GetTickCount();

				HDC hdc = GetDC(hWnd);

				const int HorizRes = pMainWnd->m_tracer.getHorizontalResolution();
				const int VertRes  = pMainWnd->m_tracer.getVerticalResolution();

				size_t imageSize = {};
				std::unique_ptr<COLORREF[]> buff = pMainWnd->m_tracer.getRawDataBGR(imageSize);

				BITMAPINFO info = {};
				info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				info.bmiHeader.biBitCount = 32;    // not 24 because COLORREF is 0x00bbggrr
				info.bmiHeader.biWidth = HorizRes;
				info.bmiHeader.biHeight = VertRes;
				info.bmiHeader.biPlanes = 1;
				info.bmiHeader.biSizeImage = 0;
				info.bmiHeader.biCompression = BI_RGB;

				// The image should be flipped vertically.
				int lines = StretchDIBits(hdc,
					0, VertRes, HorizRes, -VertRes,    // destination rectangle
					0, 0, HorizRes, VertRes,           // source rectangle
					buff.get(), &info, DIB_RGB_COLORS, SRCCOPY);

				ATLASSERT(   GDI_ERROR != lines
					      && 0         != lines);

				ReleaseDC(hWnd, hdc);

				DWORD tick2 = GetTickCount() - tick1;

				int tmp1 = 1;
			}
			return 0;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		if (pMainWnd)
		{
			pMainWnd->m_clientWidth  = LOWORD(lParam);
			pMainWnd->m_clientHeight = HIWORD(lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK MainWindow::aboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
