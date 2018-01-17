#pragma once


namespace GreenTopazTracerApp
{
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE hInstance, int nCmdShow);

		virtual ~MainWindow();

		int runMessageLoop();

	private:
		ATOM registerWndClass();

		BOOL initInstance(int nCmdShow);

		static LRESULT CALLBACK mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static INT_PTR CALLBACK aboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		// Application instance.
		HINSTANCE m_hAppInstance;

		// Main window handle.
		HWND m_hMainWindow;

		static const int MAX_LOADSTRING = 100;

		// The title bar text
		WCHAR m_titleBarStr[MAX_LOADSTRING];

		// The main window class name.
		WCHAR m_windowClassName[MAX_LOADSTRING];
	};
}
