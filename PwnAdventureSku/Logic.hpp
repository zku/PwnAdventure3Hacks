#pragma once

// Windows.
#include <Windows.h>

// Standard.
#include <memory>

// Pwny.
#include "Detour.hpp"

namespace pwny
{
	enum class LogicState { Unload, KeepGoing };

	class Logic
	{
	public:
		LogicState Pulse(float deltaTime);

	private:
		DWORD m_lastTeleportTime;
		std::unique_ptr<Detour> m_endFrameDetour;
		bool m_endFrameHookApplied;
	};
} // pwny