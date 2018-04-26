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
	: m_hAppInstance(hInstance), m_hMainWindow(nullptr), 
	  m_clientWidth(clientWidth), m_clientHeight(clientHeight),
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
		assert(false); throw EXCEPTION(L"initInstance() failed");
	}

	if (!SetTimer(m_hMainWindow, IDT_TRACE_RESULT_TIMER, 500, (TIMERPROC)nullptr))
	{
		assert(false); throw EXCEPTION_FMT(L"SetTimer() failed: %u", GetLastError());
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
		std::wcerr << L"AdjustWindowRect() failed: " << GetLastError() << std::endl;
		return FALSE;
	}

	// Pass pointer to this class instance in the last argument of CreateWindow().
	m_hMainWindow = CreateWindow(m_windowClassName, m_titleBarStr, WindowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
		nullptr, nullptr, m_hAppInstance, this);
	if (!m_hMainWindow)
	{
		std::wcerr << L"CreateWindow() failed: " << GetLastError() << std::endl;
		return FALSE;
	}

	std::wcout << L"Created main window\n";

	ShowWindow(m_hMainWindow, nCmdShow);
	UpdateWindow(m_hMainWindow);

	return TRUE;
}

int MainWindow::runMessageLoop()
{
	HACCEL hAccelTable = LoadAccelerators(m_hAppInstance, MAKEINTRESOURCE(IDC_GREENTOPAZTRACER));

#if 1
	BOOL exit = FALSE;
	DWORD exitCode = {};

	MSG msg = {};

	// We rely on the fact that if any thread exits, the ray tracing is finished.
	HANDLE hThread = m_tracer.m_threads[0];

	while (!exit)
	{
		DWORD waitStatus = MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLEVENTS);
		//DWORD waitStatus = MsgWaitForMultipleObjects(ThreadCount, &m_tracer.m_evTracingComplete.m_h, FALSE, 10000, QS_ALLEVENTS);

		switch (waitStatus)
		{
		case WAIT_OBJECT_0:        // ray tracing complete
			{
				// Export the resulting image.
				UINT stride = {};
				UINT bufferSize = {};

				std::unique_ptr<BYTE[]> spImageData = m_tracer.exportForWicImageProcessor(stride, bufferSize);

				ImageProcessor imgProcessor;
				const std::wstring filePath = L"file1.png";

				bool res = imgProcessor.saveAsPng(filePath, m_tracer.getHorizontalResolution(), m_tracer.getVerticalResolution(), 
					spImageData, stride, bufferSize);
				if (!res)
				{
					std::wcerr << L"Failed to save the ray traced image\n";
					assert(false); return 1;
				}

				// TODO: temp
#if 0
				HDC hdc = GetDC(m_hMainWindow);

				const int HorizRes = m_tracer.getHorizontalResolution();
				const int VertRes  = m_tracer.getVerticalResolution();

				size_t imageSize = {};
				std::unique_ptr<COLORREF[]> buff = m_tracer.getRawData(imageSize);

				size_t offset = {};

				for (int y = 0; y < VertRes; ++y)
				{
					for (int x = 0; x < HorizRes; ++x)
					{
						SetPixel(hdc, x, y, buff[offset++]);
					}
				}

				ReleaseDC(m_hMainWindow, hdc);

				Sleep(5000);
#endif
			}
			return 0;
		case WAIT_FAILED:
			std::wcerr << __FUNCTIONW__ << L"Unexpected wait status: " << waitStatus << '\n';
			assert(false); return 2;
		default:    // message arrived
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))    // get next message in the queue
			{
				if (WM_QUIT == msg.message)
				{
					exit = TRUE;
					exitCode = msg.wParam;
					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			break;
		}
	}

	return (int)exitCode;
#else
	// Without displaying ray tracing results.

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
#endif
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
		// Step 2 (option A). Store the window pointer.
		pMainWnd = (MainWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (!pMainWnd)
		{
			std::wcerr << L"Main window pointer is NULL\n";
			assert(false);
		}

		pMainWnd->m_tracer.traceScene();
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
				HDC hdc = GetDC(hWnd);

				const int HorizRes = pMainWnd->m_tracer.getHorizontalResolution();
				const int VertRes  = pMainWnd->m_tracer.getVerticalResolution();

				size_t imageSize = {};
				std::unique_ptr<COLORREF[]> buff = pMainWnd->m_tracer.getRawData(imageSize);

				size_t offset = {};

				for (int y = 0; y < VertRes; ++y)
				{
					for (int x = 0; x < HorizRes; ++x)
					{
						SetPixel(hdc, x, y, buff[offset++]);
					}
				}

				ReleaseDC(hWnd, hdc);
			}
			return 0;
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			// TODO: uncomment
#if 0
			const int HorizRes = pMainWnd->m_tracer.getHorizontalResolution();
			const int VertRes  = pMainWnd->m_tracer.getVerticalResolution();

			size_t imageSize = {};
			std::unique_ptr<COLORREF[]> buff = pMainWnd->m_tracer.getRawData(imageSize);

			size_t offset = {};

			for (int row = 0; row < VertRes; ++row)
			{
				for (int col = 0; col < HorizRes; ++col)
				{
					SetPixel(hdc, row, col, buff[offset++]);
				}
			}
#endif

			EndPaint(hWnd, &ps);
		}
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
