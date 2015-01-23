#include "Tick.hpp"

// Pwny.
#include "Internals.hpp"

namespace pwny
{
	std::unique_ptr<Detour> Tick::s_tickDetour;
	std::unique_ptr<Logic> Tick::s_logic;

	void Tick::Initialize()
	{
		s_logic.reset(new Logic{});
		s_tickDetour.reset(new Detour{ Rebase(Offsets::kGameAPI_Tick), reinterpret_cast<DWORD>(&Tick::GameAPI_Tick_Hook) });
		s_tickDetour->Apply();
	}

	void __fastcall Tick::GameAPI_Tick_Hook(GameAPI* pThis, DWORD edxIgnore, float deltaTime)
	{
		s_tickDetour->Remove();
		auto const native = reinterpret_cast<tGameAPI_Tick>(Rebase(Offsets::kGameAPI_Tick));

		// Call original.
		native(pThis, deltaTime);

		// Pulse framework.
		if (s_logic->Pulse(deltaTime) == LogicState::Unload)
		{
			// Logic module requested to unload the hack, so lets do it without re-applying the detour.
			_beginthread(&Tick::UnloadRoutine, 0, nullptr);
			return;
		}

		// We can keep going, so reapply the hook.
		s_tickDetour->Apply();
	}

	void __cdecl Tick::UnloadRoutine(void* arg)
	{
		Sleep(750);
		FreeLibraryAndExitThread(GetModuleHandleA("PwnAdventureSku.dll"), 0);
	}
} // pwny