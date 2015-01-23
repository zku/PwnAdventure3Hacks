#pragma once

// Windows.
#include <Windows.h>

namespace pwny
{
	enum class LogicState { Unload, KeepGoing };

	class Logic
	{
	public:
		LogicState Pulse(float deltaTime);

	private:
		DWORD m_lastTeleportTime;
	};
} // pwny