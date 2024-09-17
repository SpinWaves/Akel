// Copyright (C) 2024 kbz_8 ( contact@kbz8.me )
// This file is a part of Akel
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef __AK_ELTM_TOKEN__
#define __AK_ELTM_TOKEN__

#include <Plugins/ELTM/PreCompiled.h>
#include <Plugins/ELTM/StreamStack.h>
#include <Utils/Overloaded.h>
#include <Utils/ConstMap.h>

namespace Ak
{
	enum class EltmToken
	{
		kw_get,
		kw_let,
		kw_end,
		kw_begin,
		kw_import,
		kw_module,

		assign,

		par_open,
		par_close,
	};

	struct Eof{};
	struct Identifier{ std::string name; };

	inline constexpr bool operator==(const Eof&, const Eof&) noexcept { return true; }
	inline constexpr bool operator!=(const Eof&, const Eof&) noexcept { return false; }
	inline bool operator==(const Identifier& id1, const Identifier& id2) { return id1.name == id2.name; }
	inline bool operator!=(const Identifier& id1, const Identifier& id2) { return id1.name != id2.name; }

	using TokenValue = std::variant<EltmToken, std::string, Eof, Identifier>;

	class Token
	{
		public:
			Token(TokenValue value, std::size_t line) : m_value(std::move(value)), m_line(line) {}

			inline bool IsEof() const { return std::holds_alternative<Eof>(m_value); }
			inline bool IsString() const { return std::holds_alternative<std::string>(m_value); }
			inline bool IsKeyword() const { return std::holds_alternative<EltmToken>(m_value); }
			inline bool IsIdentifier() const { return std::holds_alternative<Identifier>(m_value); }

			inline EltmToken GetKeyword() const{ return std::get<EltmToken>(m_value); }
			inline const std::string& GetString() const{ return std::get<std::string>(m_value); }
			inline const Identifier& GetIdentifier() const { return std::get<Identifier>(m_value); }
			inline const TokenValue& GetValue() const { return m_value; }

			inline std::size_t GetLine() const noexcept { return m_line; }

			inline bool HasValue(TokenValue value) const { return m_value == std::move(value); }

		private:
			TokenValue m_value;
			std::size_t m_line;
	};

	std::optional<EltmToken> GetKeyword(const std::string& word);
	std::optional<EltmToken> GetOperator(StreamStack& stream);
}

namespace std
{
	std::string to_string(Ak::EltmToken t);

	inline std::string to_string(const Ak::TokenValue& t)
    {
		return std::visit(Ak::Overloaded{
			[](Ak::EltmToken tok) { return to_string(tok); },
			[](const std::string& str) { return str; },
			[](const Ak::Identifier& id) { return id.name; },
			[](Ak::Eof) { return std::string("<EOF>"); }
		}, t);
	}
}

#endif // __AK_ELTM_TOKEN__

