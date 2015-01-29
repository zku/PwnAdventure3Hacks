// Windows.
#include <Windows.h>
#include <process.h>

// Standard.
#include <string>

// Boost.
#include <boost/format.hpp>

// Pwny.
#include "Tick.hpp"

namespace pwny
{
	void __cdecl InitializeHackingFramework(void* arg)
	{
		Tick::Initialize();
	}
} // pwny

extern "C" __declspec(dllexport) void EntryPoint()
{
	_beginthread(&pwny::InitializeHackingFramework, 0, nullptr);
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
	return TRUE;
}