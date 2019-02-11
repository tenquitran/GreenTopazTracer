#pragma once


namespace GreenTopazTracerApp
{
	// Used to get row and column of the next pixel.
	class PixelCounter
	{
	public:
		PixelCounter(int horizontalResolution, int verticalResolution)
			: HorizontalResolution(horizontalResolution), VerticalResolution(verticalResolution)
		{
			InitializeCriticalSection(&m_cs);
		}

		~PixelCounter()
		{
			DeleteCriticalSection(&m_cs);
		}

		// Get row and column of the next pixel.
		// Parameters: row, column - valid only if the function returns true.
		// Returns: true if there are pixels to process, false if the tracing is finished.
		bool getNext(int& row, int& column)
		{
			EnterCriticalSection(&m_cs);

			// Once any thread finished tracing, this will prevent other threads from continuing.
			if (m_row >= VerticalResolution)
			{
				LeaveCriticalSection(&m_cs);
				return false;    // finished tracing
			}

			if (++m_column >= HorizontalResolution)
			{
				m_column = 0;

				if (++m_row >= VerticalResolution)
				{
					LeaveCriticalSection(&m_cs);
					return false;    // finished tracing
				}
			}

			column = m_column;
			row = m_row;

			LeaveCriticalSection(&m_cs);
			return true;
		}

	private:
        const int HorizontalResolution = {};
        const int VerticalResolution   = {};

		// Current row and column.
        int m_row    = {};
        int m_column = { -1 };

		CRITICAL_SECTION m_cs;
	};
}
