// Windows.
#include <Windows.h>
#include <process.h>

// Standard.
#include <string>

// Boost.
#include <boost/format.hpp>

// Pwny.
#include "Internals.hpp"
#include "Hacks.hpp"

namespace pwny
{
	volatile bool g_loaded;

	void __cdecl InitializeHackingFramework(void* arg)
	{
		// A simple infinite loop that keeps checking keys F1 and F2:
		// F1: Teleport forward, approx. 10 meters.
		// F2: Stop the infinite loop.

		// TODO: Hook into WndProc instead, this is garbage and you know it!
		// TODO: Hook into the rendering to display fancy things.
		// TODO: Hook into the chat routine to parse commands for the framework instead.

		g_loaded = true;

		DWORD lastTeleport = 0;
		while (g_loaded)
		{
			DWORD const currentTime = GetTickCount();
			
			// Enforce a small wait time between teleports, reducing the crash/disconnect risk.
			if (currentTime - lastTeleport > 1000)
			{
				if (GetAsyncKeyState(VK_F1) & 1)
				{
					hacks::TeleportForward(1500.0f);
					lastTeleport = currentTime;
				}
			}

			if (GetAsyncKeyState(VK_F2) & 1)
			{
				break;
			}

			Sleep(100);
		}
	}

	void __cdecl Unload(void* arg)
	{
		g_loaded = false;
		Sleep(250);

		// Ugly hack, but it works.
		auto const hModule = GetModuleHandleA("PwnAdventureSku.dll");
		FreeLibrary(hModule); // The loader increments the count, so we have to do it twice.
		FreeLibraryAndExitThread(hModule, 0);
	}
} // pwny

extern "C" __declspec(dllexport) void EntryPoint()
{
	_beginthread(&pwny::InitializeHackingFramework, 0, nullptr);
}

extern "C" __declspec(dllexport) void ExitPoint()
{
	_beginthread(&pwny::Unload, 0, nullptr);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
	return TRUE;
}