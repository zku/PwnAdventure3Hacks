#include "Tick.hpp"

// Pwny.
#include "Internals.hpp"

namespace pwny
{
	std::unique_ptr<Detour> Tick::s_tickDetour;
	std::unique_ptr<Detour> Tick::s_endFrameDetour;
	std::unique_ptr<Detour> Tick::s_wndProcDetour;
	std::unique_ptr<Logic> Tick::s_logic;
	std::unique_ptr<Graphics> Tick::s_graphics;
	std::unique_ptr<Input> Tick::s_input;

	void Tick::Initialize()
	{
		s_logic.reset(new Logic{});
		s_tickDetour.reset(new Detour{ RebaseModule(Offsets::kGameAPI_Tick), reinterpret_cast<DWORD>(&Tick::GameAPI_Tick_Hook) });
		s_tickDetour->Apply();
	}

	void __fastcall Tick::GameAPI_Tick_Hook(GameAPI* pThis, DWORD edxIgnore, float deltaTime)
	{
		s_tickDetour->Remove();

		// Call original.
		auto const native = reinterpret_cast<decltype(&Tick::GameAPI_Tick_Hook)>(s_tickDetour->GetAddress());
		native(pThis, edxIgnore, deltaTime);

		// Initialize graphics if necessary.
		if (!s_graphics && !s_endFrameDetour)
		{
			s_graphics.reset(new Graphics{});
			s_endFrameDetour.reset(new Detour{ RebaseGame(Offsets::kEndFrame), reinterpret_cast<DWORD>(&Tick::EndFrame_Hook) });
			s_endFrameDetour->Apply();
		}

		// Initialize input if necessary.
		if (!s_input && !s_wndProcDetour && s_graphics)
		{
			auto const hWnd = s_graphics->GetWindowHandle();
			if (hWnd)
			{
				auto const wndProc = static_cast<DWORD>(GetWindowLongPtrW(hWnd, GWL_WNDPROC));
				if (wndProc)
				{
					s_input.reset(new Input{});
					s_wndProcDetour.reset(new Detour{ wndProc, reinterpret_cast<DWORD>(&Tick::WndProc_Hook) });
					s_wndProcDetour->Apply();
				}
			}
		}

		// Pulse framework.
		if (s_logic->Pulse(deltaTime) == LogicState::Unload)
		{
			if (s_graphics && s_endFrameDetour)
			{
				s_endFrameDetour->Remove();
			}

			if (s_input && s_wndProcDetour)
			{
				s_wndProcDetour->Remove();
			}

			// Unload module from another thread, game thread needs to survive.
			_beginthread(&Tick::UnloadRoutine, 0, nullptr);
			return;
		}

		// We can keep going, so reapply the hook.
		s_tickDetour->Apply();
	}

	void __fastcall Tick::EndFrame_Hook(UE4Graphics* pThis, DWORD edxIgnore, DWORD unk1, DWORD unk2, DWORD unk3)
	{
		// Do our own drawing here.
		s_graphics->Draw(pThis);

		// Call original.
		s_endFrameDetour->Remove();
		auto const native = reinterpret_cast<decltype(&Tick::EndFrame_Hook)>(s_endFrameDetour->GetAddress());
		native(pThis, edxIgnore, unk1, unk2, unk3);
		s_endFrameDetour->Apply();
	}

	LRESULT __stdcall Tick::WndProc_Hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (!s_input->Process(hWnd, msg, wParam, lParam))
		{
			s_wndProcDetour->Remove();
			auto const native = reinterpret_cast<decltype(&Tick::WndProc_Hook)>(s_wndProcDetour->GetAddress());
			LRESULT const result = native(hWnd, msg, wParam, lParam);
			s_wndProcDetour->Apply();
			return result;
		}

		return 0;
	}

	void __cdecl Tick::UnloadRoutine(void* arg)
	{
		Sleep(750);
		FreeLibraryAndExitThread(GetModuleHandleA("PwnAdventureSku.dll"), 0);
	}
} // pwny