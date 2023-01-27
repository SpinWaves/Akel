// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 27/08/2022

#ifndef __AK_ELTM_TOKEN__
#define __AK_ELTM_TOKEN__

#include <Akpch.h>
#include <Utils/utils.h>
#include "streamStack.h"

namespace Ak
{
	enum class eltm_token
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

	struct eof{};
	struct identifier{ std::string name; };
	inline constexpr bool operator==(const eof&, const eof&) noexcept { return true; }
	inline constexpr bool operator!=(const eof&, const eof&) noexcept { return false; }
	inline bool operator==(const identifier& id1, const identifier& id2) { return id1.name == id2.name; }
	inline bool operator!=(const identifier& id1, const identifier& id2) { return id1.name != id2.name; }

	using token_value = std::variant<eltm_token, std::string, eof, identifier>;

	class Token
	{
		public:
			Token(token_value value, std::size_t line) : _value(std::move(value)), _line(line) {}

			static inline duets_array<eltm_token, std::string> keyword_token
			{
				{eltm_token::kw_get, "get"},
				{eltm_token::kw_end, "end"},
				{eltm_token::kw_let, "let"},
				{eltm_token::kw_begin, "begin"},
				{eltm_token::kw_import, "import"},
				{eltm_token::kw_module, "module"},
			};

			static inline duets_array<eltm_token, std::string> operators_token
			{
				{eltm_token::assign, "="},

				{eltm_token::par_open, "("},
				{eltm_token::par_close, ")"},
			};

			inline bool is_eof()	const { return std::holds_alternative<eof>(_value); }
			inline bool is_string()	const { return std::holds_alternative<std::string>(_value); }
			inline bool is_keyword()	const { return std::holds_alternative<eltm_token>(_value); }
			inline bool is_identifier()	const { return std::holds_alternative<identifier>(_value); }
			
			inline eltm_token get_keyword()			const{ return std::get<eltm_token>(_value); }
			inline const std::string& get_string()	const{ return std::get<std::string>(_value); }
			inline const identifier& get_identifier() const { return std::get<identifier>(_value); }
			inline const token_value& get_value() const { return _value; }

			inline std::size_t get_line() const noexcept { return _line; }

			inline bool has_value(token_value value) const { return _value == std::move(value); }

		private:
			token_value _value;
			std::size_t _line;
	};

	inline std::optional<eltm_token> get_keyword(const std::string& word)
	{
		return !Token::keyword_token.has(word) ? std::nullopt : std::make_optional(Token::keyword_token[word]);
	}
	inline std::optional<eltm_token> get_operator(StreamStack& stream)
	{
		std::string c(1, (char)stream());
		return Token::operators_token.has(c) ? std::make_optional(Token::operators_token[c]) : std::nullopt;
	}
}

namespace std
{
	inline std::string to_string(Ak::eltm_token t)
	{
		return Ak::Token::keyword_token.has(t)
					? std::string(Ak::Token::keyword_token[t])
					: std::string(Ak::Token::operators_token[t]);
	}

	inline std::string to_string(const Ak::token_value& t)
    {
		return std::visit(Ak::overloaded
        {
			[](Ak::eltm_token tok) { return to_string(tok); },
			[](const std::string& str) { return str; },
			[](const Ak::identifier& id) { return id.name; },
			[](Ak::eof) { return std::string("<EOF>"); }
		}, t);
	}
}

#endif // __AK_ELTM_TOKEN__

