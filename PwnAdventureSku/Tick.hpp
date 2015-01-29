#pragma once

// Windows.
#include <Windows.h>
#include <process.h>

// Pwny.
#include "Detour.hpp"
#include "Internals.hpp"
#include "Logic.hpp"
#include "Graphics.hpp"
#include "Input.hpp"

namespace pwny
{
	class Tick
	{
	public:
		static void Initialize();

	private:
		static void __fastcall GameAPI_Tick_Hook(GameAPI* pThis, DWORD edxIgnore, float deltaTime);
		static void __fastcall EndFrame_Hook(UE4Graphics* pThis, DWORD edxIgnore, DWORD unk1, DWORD unk2, DWORD unk3);
		static LRESULT __stdcall WndProc_Hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static void __cdecl UnloadRoutine(void* arg);

		static std::unique_ptr<Detour> s_tickDetour;
		static std::unique_ptr<Detour> s_endFrameDetour;
		static std::unique_ptr<Detour> s_wndProcDetour;
		static std::unique_ptr<Logic> s_logic;
		static std::unique_ptr<Graphics> s_graphics;
		static std::unique_ptr<Input> s_input;
	};
} // pwny