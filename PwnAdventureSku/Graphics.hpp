#pragma once

// Windows.
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

// AntTweakBar.
#include <AntTweakBar.h>

// Pwny.
#include "Internals.hpp"

namespace pwny
{
	class Graphics
	{
	public:
		Graphics();
		void Draw(UE4Graphics* graphics);
		HWND GetWindowHandle() const;

	private:
		bool m_initialized;
		TwBar* m_bar;
		HWND m_hWnd;
	};
} // pwny