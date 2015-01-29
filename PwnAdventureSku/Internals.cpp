#include "Internals.hpp"

namespace pwny
{
	DWORD GetModuleBaseAddress()
	{
		static DWORD moduleBaseAddress = reinterpret_cast<DWORD>(GetModuleHandleA("GameLogic.dll"));
		return moduleBaseAddress;
	}

	DWORD RebaseModule(DWORD address)
	{
		return GetModuleBaseAddress() + address;
	}

	GameAPI* GetGameAPIObject()
	{
		return *reinterpret_cast<GameAPI**>(RebaseModule(Offsets::kGameAPI));
	}

	World* GetWorldObject()
	{
		return *reinterpret_cast<World**>(RebaseModule(Offsets::kWorld));
	}

	IPlayer* GetMe()
	{
		return *reinterpret_cast<IPlayer**>(RebaseModule(Offsets::kPlayer));
	}

	Player* IPlayer::GetPlayer() const
	{
		// This seems like a really ugly hack, but I couldn't find any (global)
		// reference to the actual Player instance.
		auto const address = reinterpret_cast<DWORD>(this);
		return reinterpret_cast<Player*>(address - sizeof(Actor));
	}

	std::vector<LocationAndRotation> GameAPI::GetNamedLocationPointList(std::string const& location)
	{
		// Replicate behavior of their GetNamedLocationPointList implementation.

		std::vector<LocationAndRotation> locations;
		LocationAndRotation* list;
		int count = this->vfptr->GetNamedLocationPoints(this, location.c_str(), &list);
		
		for (int i = 0; i < count; ++i)
		{
			locations.push_back(list[i]);
		}

		this->vfptr->FreeNamedLocationPoints(this, list);
		return locations;
	}

	DWORD GetGameBaseAddress()
	{
		static DWORD gameBaseAddress = reinterpret_cast<DWORD>(GetModuleHandleA(nullptr));
		return gameBaseAddress;
	}

	DWORD RebaseGame(DWORD address)
	{
		return GetGameBaseAddress() + address;
	}

	UE4Graphics* GetGraphicsObject()
	{
		return *reinterpret_cast<UE4Graphics**>(RebaseGame(Offsets::kGraphicsObject));
	}
} // pwny