#pragma once

#include "GreenTopazTracer.h"


namespace GreenTopazTracerApp
{
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE hInstance, int nCmdShow, int clientWidth, int clientHeight);

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

		static const int MaxLoadString = 100;

		// The title bar text
		WCHAR m_titleBarStr[MaxLoadString];

		// The main window class name.
		WCHAR m_windowClassName[MaxLoadString];

		// Width and height of the window.
		int m_clientWidth;
		int m_clientHeight;

		// Ray tracer.
		GreenTopazTracer m_tracer;
	};
}
