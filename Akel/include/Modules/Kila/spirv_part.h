// This file is a part of Akel
// Authors : @kbz_8
// Created : 26/10/2022
// Updated : 28/10/2022

#ifndef __AK_KILA_SPIRV_PART__
#define __AK_KILA_SPIRV_PART__

#include <Akpch.h>
#include "spirv_data.h"

namespace Ak::Kl
{
	class SpvPart
	{
		// TODO : take care of little endian and big endian

		public:
			SpvPart() = default;

			template <typename ... Args>
			void add(Spv opcode, const Args& ... args);
			
			template <typename T>
			inline void addraw(const T& value) { addraw(static_cast<uint32_t>(value)); }
			inline void addraw(uint32_t val) noexcept { _code.push_back(val); }
			inline void addraw(const char* str) { addraw(std::string_view(str)); }
			inline void addraw(std::string str) { addraw(std::string_view(str)); }
			void addraw(std::string_view str);
			inline void addraw(std::initializer_list<uint32_t> raw_data)
			{
				for(uint32_t part : raw_data)
					addraw(part);
			}

			inline const std::vector<uint32_t>& getCode() const noexcept { return _code; }
			inline void clearData() { _code.clear(); }

			~SpvPart() = default;

		private:
			inline uint32_t buildOpCode(Spv opcode, uint32_t wc) const noexcept { return static_cast<uint32_t>(opcode) | wc << 16; }

			template <typename T>
			inline constexpr uint32_t countWord(const T&) const noexcept { return 1; }
			inline uint32_t countWord(const char* str) { return countWord(std::string_view(str)); }
			inline uint32_t countWord(std::string str) { return countWord(std::string_view(str)); }
			inline uint32_t countWord(std::string_view str) { return (static_cast<uint32_t>(str.size() + 1) + sizeof(uint32_t) - 1) / sizeof(uint32_t); }

			std::vector<uint32_t> _code;
	};

	template <typename ... Args>
	void SpvPart::add(Spv opcode, const Args& ... args)
	{
		uint32_t wc = 1 + (countWord(args) + ... + 0);

		if constexpr(sizeof...(args) > 0)
			(addraw(args), ...);
	}
}

#endif // __AK_KILA_SPIRV_PART__
