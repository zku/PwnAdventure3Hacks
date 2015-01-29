#include "Graphics.hpp"

// Standard.
#include <string>

// Boost.
#include <boost/format.hpp>

namespace pwny
{
	Graphics::Graphics()
		: m_initialized(false)
		, m_hWnd(nullptr)
	{ }

	// Useless for now, just to test.
	float g_movementSpeed = 5000.0f;
	bool g_teleport = true;

	void Graphics::Draw(UE4Graphics* graphics)
	{
		if (!m_initialized)
		{
			// Create AntTweakBar UI.
			// TODO: Actually make this usable.. but it looks pretty!
			TwInit(TW_DIRECT3D11, graphics->m_device);
			m_bar = TwNewBar("PwnAdventureSku");
			int barSize[2] = { 224, 320 };
			TwSetParam(m_bar, NULL, "size", TW_PARAM_INT32, 2, barSize);
			TwAddVarRW(m_bar, "F1 to teleport", TW_TYPE_BOOLCPP, &g_teleport, "");
			TwAddVarRW(m_bar, "Movement speed", TW_TYPE_FLOAT, &g_movementSpeed, "min=1 max=10000");
			
			// Only need to do this once, afterwards the WndProc event handler should handle resizes properly.
			DXGI_SWAP_CHAIN_DESC desc = { 0 };
			graphics->m_unkChain->m_swapChain->GetDesc(&desc);
			m_hWnd = desc.OutputWindow;

			RECT r;
			GetClientRect(m_hWnd, &r);
			TwWindowSize(r.right - r.left, r.bottom - r.top);

			m_initialized = true;
		}

		TwDraw();
	}

	HWND Graphics::GetWindowHandle() const
	{
		return m_hWnd;
	}
} // pwny