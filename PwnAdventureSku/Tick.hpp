#pragma once

// Windows.
#include <Windows.h>
#include <process.h>

// Pwny.
#include "Detour.hpp"
#include "Internals.hpp"
#include "Logic.hpp"

namespace pwny
{
	class Tick
	{
	public:
		static void Initialize();

	private:
		typedef void(__thiscall * tGameAPI_Tick)(GameAPI*, float);
		static void __fastcall GameAPI_Tick_Hook(GameAPI* pThis, DWORD edxIgnore, float deltaTime);
		static void __cdecl UnloadRoutine(void* arg);

		static std::unique_ptr<Detour> s_tickDetour;
		static std::unique_ptr<Logic> s_logic;
	};
} // pwny