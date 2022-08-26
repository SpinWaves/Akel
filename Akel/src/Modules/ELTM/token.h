// This file is a part of Akel
// Authors : @kbz_8
// Created : 05/05/2021
// Updated : 26/08/2022

#ifndef __AK_ELTM_TOKEN__
#define __AK_ELTM_TOKEN__

#include <Akpch.h>

namespace Ak
{
	enum class eltm_token
	{
		kw_get,
		kw_set,
		kw_end,
		kw_begin,
		kw_import,
		kw_module,

		assign,
	};

	struct eof{};
	struct identifier{ std::string name; };
	inline constexpr bool operator==(const eof&, const eof&) noexcept { return true; }
	inline constexpr bool operator!=(const eof&, const eof&) noexcept { return false; }
	inline bool operator==(const identifier& id1, const identifier& id2) { return id1.name == id2.name; }
	inline bool operator!=(const identifier& id1, const identifier& id2) { return id1.name != id2.name; }

	class Token
	{
		public:
			Token(std::variant<eltm_token, std::string, eof, identifier> value, std::size_t line) : _value(std::move(value)), _line(line) {}

			static inline duets_array<eltm_token, std::string> keyword_token
			{
				{eltm_token::kw_get, "get"},
				{eltm_token::kw_end, "end"},
				{eltm_token::kw_set, "let"},
				{eltm_token::kw_begin, "begin"},
				{eltm_token::kw_import, "import"},
				{eltm_token::kw_module, "module"},
			};

			static inline duets_array<eltm_token, std::string> operators_token
			{
				{eltm_token::assign, "="},
			};

			inline bool is_eof()	const { return std::holds_alternative<eof>(_value); }
			inline bool is_string()	const { return std::holds_alternative<std::string>(_value); }
			inline bool is_keyword()	const { return std::holds_alternative<eltm_token>(_value); }
			inline bool is_identifier()	const { return std::holds_alternative<identifier>(_value); }
			
			inline eltm_token get_keyword()			const{ return std::get<eltm_token>(_value); }
			inline const std::string& get_string()	const{ return std::get<std::string>(_value); }
			inline const identifier& get_identifier() const { return std::get<identifier>(_value); }

			inline std::size_t get_line() const noexcept { return _line; }

			inline bool has_value(std::variant<eltm_token, std::string, eof, identifier> value) const { return _value == std::move(value); }

		private:
			std::variant<eltm_token, std::string, eof, identifier> _value;
			std::size_t _line;
	};

	inline std::optional<eltm_token> get_keyword(const std::string& word)
	{
		return !Token::keyword_tokens.has(word) ? std::nullopt : std::make_optional(Token::keyword_token[word]);
	}
	inline std::optional<eltm_token> get_operator(class StreamStack& stream)
	{
		char c = stream();
		return Token::operators_token.has(c) ? std::make_optional(Token::operators_token[c]) : std::nullopt;
	}
}

#endif // __AK_ELTM_TOKEN__

