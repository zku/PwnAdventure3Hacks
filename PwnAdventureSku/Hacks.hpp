#pragma once

// Standard.
#include <string>

// Pwny.
#include "Internals.hpp"

namespace pwny
{
	namespace hacks
	{
		// Teleport to the actor with the given name (substring match).
		// Examples: Michael, Payne
		void TeleportToActor(std::string const& name);

		// Teleport to given world position.
		void TeleportTo(Vector3* position);

		// Teleport distance into the current direction.
		// Note: 1000 units look like 5 meters, so these values can be rather large.
		void TeleportForward(float distance);

		// Adjust player walking speed (speedhack).
		void SetPlayerSpeed(float speed);

		// Send chat message. Don't overdo.
		void Chat(std::string const& message);

		// Get the world position of a named location, useful for teleportation.
		// Examples: BlockySpawnPoint, GoldFarmSpawnPoint, MagmarokSpawner
		Vector3 GetNamedLocation(std::string const& location);
	} // hacks
} // pwny