// This file is a part of Akel
// Authors : @kbz_8
// Created : 01/02/2024
// Updated : 01/02/2024

#include <Plugins/ELTM/Token.h>

namespace Ak
{
	const ConstMap<std::string_view, EltmToken> keyword_tokens{
		{"get", EltmToken::kw_get},
		{"end", EltmToken::kw_end},
		{"let", EltmToken::kw_let},
		{"begin", EltmToken::kw_begin},
		{"import", EltmToken::kw_import},
		{"module", EltmToken::kw_module},
	};

	const ConstMap<std::string_view, EltmToken> operator_tokens{
		{"=", EltmToken::assign},
		{"(", EltmToken::par_open},
		{")", EltmToken::par_close},
	};

	std::optional<EltmToken> GetKeyword(const std::string& word)
	{
		return keyword_tokens.Has(word) ? std::make_optional(keyword_tokens.Find(word)->second) : std::nullopt;
	}

	std::optional<EltmToken> GetOperator(StreamStack& stream)
	{
		std::string c(1, static_cast<char>(stream()));
		return operator_tokens.Has(c) ? std::make_optional(operator_tokens.Find(c)->second) : std::nullopt;
	}
}

namespace std
{
	std::string to_string(Ak::EltmToken t)
	{
		for(auto [str, token] : Ak::keyword_tokens)
		{
			if(t == token)
				return std::string{str};
		}
		for(auto [str, token] : Ak::operator_tokens)
		{
			if(t == token)
				return std::string{str};
		}
		return {};
	}
}
