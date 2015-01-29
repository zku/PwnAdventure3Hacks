#include "Input.hpp"

// AntTweakBar.
#include <AntTweakBar.h>

namespace pwny
{
	Input::Input()
		: m_initialized(true)
	{ }

	bool Input::Process(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// TODO: Show cursor and block window events from the game, e.g. when some key is down.
		return TwEventWin(hWnd, msg, wParam, lParam) != 0;
	}
} // pwny