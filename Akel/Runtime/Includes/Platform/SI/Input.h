// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/02/2024
// Updated : 11/02/2024

#ifndef __AK_PLATFORM_SI_INPUTS__
#define __AK_PLATFORM_SI_INPUTS__

#include <Utils/NonCopyable.h>
#include <Utils/NonMovable.h>
#include <Platform/PreCompiled.h>

namespace Ak
{
	class AK_PLATFORM_API Inputs
	{
		friend class PlatformModule;

		public:
			Inputs() = default;

			virtual bool GetKeyPressed(const std::uint32_t button) const noexcept = 0;
			virtual bool GetKeyReleased(const std::uint32_t button) const noexcept = 0;

			virtual bool GetMouseButtonPressed(const std::uint8_t button) const noexcept = 0;
			virtual bool GetMouseButtonReleased(const std::uint8_t button) const noexcept = 0;

			virtual int GetX() const noexcept = 0;
			virtual int GetY() const noexcept = 0;

			virtual int GetXGlobal() const noexcept = 0;
			virtual int GetYGlobal() const noexcept = 0;

			virtual int GetXRel() const noexcept = 0;
			virtual int GetYRel() const noexcept = 0;

			inline bool IsMouseMoving() const noexcept { return GetXRel() || GetYRel(); }
			AK_FORCEINLINE bool IsRunning() const noexcept { return m_run; }
			AK_FORCEINLINE constexpr void Finish() noexcept { m_run = false; }
			AK_FORCEINLINE constexpr void Run() noexcept { m_run = true; }

			virtual ~Inputs() = default;

		protected:
			virtual void Update() = 0;

		protected:
			bool m_run = true;
	};
}

#endif
