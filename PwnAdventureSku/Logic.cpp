#include "Logic.hpp"

// Pwny.
#include "Internals.hpp"
#include "Hacks.hpp"

namespace pwny
{
	LogicState Logic::Pulse(float deltaTime)
	{
		// Unload the framework with F9.
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			return LogicState::Unload;
		}

		DWORD const currentTime = GetTickCount();

		// Teleport forward (current facing direction) with F1.
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			if (currentTime - m_lastTeleportTime > 100)
			{
				hacks::TeleportForward(1500.0f);
				m_lastTeleportTime = currentTime;
			}
		}

		// Teleport to Michael Angelo with F2.
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			if (currentTime - m_lastTeleportTime > 100)
			{
				hacks::TeleportToActor("MichaelAngelo");
				m_lastTeleportTime = currentTime;
			}
		}

		// Teleport to the blocky thing with F3.
		if (GetAsyncKeyState(VK_F3) & 1)
		{
			if (currentTime - m_lastTeleportTime > 100)
			{
				Vector3 target = hacks::GetNamedLocation("BlockySpawnPoint");
				hacks::TeleportTo(&target);
				m_lastTeleportTime = currentTime;
			}
		}

		return LogicState::KeepGoing;
	}
} // pwny