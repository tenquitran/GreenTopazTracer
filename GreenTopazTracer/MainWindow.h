#pragma once

#include "GreenTopazTracer.h"


namespace GreenTopazTracerApp
{
	class MainWindow
	{
	public:
		MainWindow(HINSTANCE hInstance, int nCmdShow, int clientWidth, int clientHeight, unsigned int threadCount);

		virtual ~MainWindow();

		int runMessageLoop();

	private:
        MainWindow(const MainWindow&) = delete;
        MainWindow& operator=(const MainWindow&) = delete;

		ATOM registerWndClass();

		BOOL initInstance(int nCmdShow);

		static LRESULT CALLBACK mainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static INT_PTR CALLBACK aboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

		// Export the ray traced image to a file.
		void exportImage();

	private:
		// Application instance.
        HINSTANCE m_hAppInstance = { nullptr };

		// Main window handle.
        HWND m_hMainWindow = { nullptr };

		static const int MaxLoadString = 100;

		// The title bar text
		WCHAR m_titleBarStr[MaxLoadString];

		// The main window class name.
		WCHAR m_windowClassName[MaxLoadString];

		// Width and height of the window.
        int m_clientWidth  = {};
        int m_clientHeight = {};

		// Ray tracer.
		GreenTopazTracer m_tracer;

		// true if the ray tracing have been started.
        bool m_rayTracingStarted = { false };
	};
}
