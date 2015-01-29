#pragma once

// Windows.
#include <Windows.h>

namespace pwny
{
	class Input
	{
	public:
		Input();
		bool Process(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		bool m_initialized;
	};
} // pwny