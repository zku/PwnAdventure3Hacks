#include "Detour.hpp"

namespace pwny
{
	ProtectGuard::ProtectGuard(DWORD address, DWORD size)
		: m_address(address)
		, m_size(size)
		, m_oldFlags(0)
	{
		VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, PAGE_EXECUTE_READWRITE, &m_oldFlags);
	}

	ProtectGuard::~ProtectGuard()
	{
		DWORD dummy = 0;
		VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, m_oldFlags, &dummy);
	}

	Detour::Detour(DWORD address, DWORD hook)
		: m_address(address)
		, m_hook(hook)
		, m_applied(false)
	{ }

	Detour::~Detour()
	{
		Remove();
	}

	bool Detour::IsApplied() const
	{
		return m_applied;
	}

	void Detour::Apply()
	{
		if (IsApplied()) return;

		// First time, grab the original bytes.
		if (m_original.empty())
		{
			for (int i = 0; i < 6; ++i)
			{
				m_original.push_back(*reinterpret_cast<unsigned char*>(m_address + i));
			}
		}

		// First time, build the jump.
		if (m_patch.empty())
		{
			m_patch.push_back(0x68); // PUSH
			for (int i = 0; i < 4; ++i)
			{
				m_patch.push_back((m_hook >> (i * 8)) & 0xff); // ADDRESS
			}
			m_patch.push_back(0xC3); // RET
		}

		ProtectGuard guard{ m_address, 6 };
		memcpy_s(reinterpret_cast<void*>(m_address), 6, m_patch.data(), 6);
		m_applied = true;
	}

	void Detour::Remove()
	{
		if (!IsApplied()) return;

		ProtectGuard guard{ m_address, 6 };
		memcpy_s(reinterpret_cast<void*>(m_address), 6, m_original.data(), 6);
		m_applied = false;
	}

	DWORD Detour::GetAddress() const
	{
		return m_address;
	}
} // pwny