# PwnAdventure3Hacks
A tiny hacking framework for the PwnAdventure3: Pwnie Island game created by http://ghostintheshellcode.com/ ( http://pwnadventure.com/ )

## Features

* Teleport
* Speedhack
* Chat


```c++
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
```


## Paltform

Windows. Make sure the MSVC runtime is compatible with the one used in the game (e.g. with Visual Studio 2013).

## Dependencies

* Windows
* Boost
* Some C++11 (VS2013)

## How to

1. Start game
2. Run `Release/RuntimeInject.bat` to inject the DLL into the game process and run the EntryPoint function. Hit F1 to teleport forward or change stuff, see `DllMain.cpp`.
3. Run `Release/RuntimeEject.bat` to unload the DLL. It's an ugly/dirty hack, but increases development speed quite a bit until some scripting support is added.

## Hacking

* Start looking at the `Internals.hpp` file to get a feel of how the internal classes work
* Look at `Hacks.cpp` for some sample hacks like teleportation
* Don't do debug builds, they will fail!

## License

* The DLL injector was not made by me. See the help output for more information.
* For the rest, see the LICENSE file