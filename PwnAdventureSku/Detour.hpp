#pragma once

// Windows.
#include <Windows.h>

// Standard.
#include <memory>
#include <vector>

namespace pwny
{
	class ProtectGuard
	{
	public:
		ProtectGuard(DWORD address, DWORD size);
		~ProtectGuard();

	private:
		DWORD m_address;
		DWORD m_size;
		DWORD m_oldFlags;
	};

	class Detour
	{
	public:
		Detour(DWORD address, DWORD hook);
		~Detour();

		bool IsApplied() const;
		void Apply();
		void Remove();

	private:
		Detour& operator=(Detour const& other);
		Detour(Detour const& other);

		std::vector<unsigned char> m_original;
		std::vector<unsigned char> m_patch;
		DWORD m_address;
		DWORD m_hook;
		bool m_applied;
	};
} // pwny