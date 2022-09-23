// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/11/2021
// Updated : 01/08/2022

#ifndef __AK_KILA_TOKENS__
#define __AK_KILA_TOKENS__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>
#include <Modules/Kila/stream_stack.h>

namespace Ak::Kl
{
    enum class Tokens
    {
		kw_do,
        kw_end,
        kw_for,
        kw_len,
        kw_mut,
		kw_break,
        kw_const,
		kw_while,
        kw_until,
        kw_struct,
		kw_return,
        kw_import,
        kw_export,
        kw_repeat,
        kw_uniform,
		kw_continue,
        kw_location,
        kw_function,

        dot,
        comma,
        colon,
        square_b,
        square_e,
        bracket_b,
        bracket_e,
        embrace_b,
        embrace_e,

        t_num,
        t_void,
        t_bool,
        t_vec2,
        t_vec3,
        t_vec4,
        t_mat2,
        t_mat3,
        t_mat4,

        b_true,
        b_false,

        statment_if,
        statment_then,
        statment_else,
        statment_elseif,

        add_assign,
        sub_assign,
        mul_assign,
        div_assign,
        mod_assign,
		
		add,
		sub,
		mul,
		div,
		mod,
        assign,

        eq,
        ne,
        lt,
        gt,
        le,
        ge,

        arrow,

        logical_or,
        logical_not,
        logical_and,

        endline
    };

    struct eof{};
    struct identifier { std::string name; };

    std::optional<Tokens> get_keyword(const std::string& word);
	std::optional<Tokens> get_operator(StreamStack& stream);

	inline bool operator==(const identifier& id1, const identifier& id2) { return id1.name == id2.name; }
	inline bool operator!=(const identifier& id1, const identifier& id2) { return id1.name != id2.name; }
	inline constexpr bool operator==(const eof&, const eof&) noexcept { return true; }
	inline constexpr bool operator!=(const eof&, const eof&) noexcept { return false; }

    using token_value = std::variant<Tokens, identifier, double, bool, eof>;

    class Token
    {
        public:
            Token(token_value value, unsigned int line);

			static inline duets_array<Tokens, std::string> kw_tokens
			{
                {Tokens::kw_do, "do"},
                {Tokens::kw_end, "end"},
                {Tokens::kw_for, "for"},
                {Tokens::kw_len, "len"},
                {Tokens::kw_mut, "mut"},
                {Tokens::kw_while, "while"},
                {Tokens::kw_break, "break"},
                {Tokens::kw_function, "fn"},
                {Tokens::kw_until, "until"},
                {Tokens::kw_struct, "struct"},
                {Tokens::kw_return, "return"},
                {Tokens::kw_import, "import"},
                {Tokens::kw_export, "export"},
                {Tokens::kw_repeat, "repeat"},
                {Tokens::kw_const, "constval"},
                {Tokens::kw_uniform, "uniform"},
                {Tokens::kw_continue, "continue"},
                {Tokens::kw_location, "location"},

                {Tokens::t_num, "num"},
                {Tokens::t_void, "void"},
                {Tokens::t_bool, "bool"},
                {Tokens::t_vec2, "vec2"},
                {Tokens::t_vec3, "vec3"},
                {Tokens::t_vec4, "vec4"},
                {Tokens::t_mat2, "mat2"},
                {Tokens::t_mat3, "mat3"},
                {Tokens::t_mat4, "mat4"},

                {Tokens::logical_or, "or"},
                {Tokens::logical_not, "not"},
                {Tokens::logical_and, "and"},

                {Tokens::b_true, "true"},
                {Tokens::b_false, "false"},

                {Tokens::statment_if, "if"},
                {Tokens::statment_then, "then"},
                {Tokens::statment_else, "else"},
                {Tokens::statment_elseif, "elseif"}
			};

			static inline duets_array<Tokens, std::string> operators_token
			{
                {Tokens::dot, "."},
                {Tokens::comma, ","},
                {Tokens::colon, ":"},
                {Tokens::square_e, "]"},
                {Tokens::square_b, "["},
                {Tokens::bracket_b, "("},
                {Tokens::bracket_e, ")"},
                {Tokens::embrace_b, "{"},
                {Tokens::embrace_e, "}"},

                {Tokens::arrow, "->"},

                {Tokens::gt, ">"},
                {Tokens::lt, "<"},
                {Tokens::eq, "=="},
                {Tokens::ne, "!="},
                {Tokens::le, "<="},
                {Tokens::ge, ">="},

                {Tokens::add_assign, "+="},
                {Tokens::sub_assign, "-="},
                {Tokens::mul_assign, "*="},
                {Tokens::div_assign, "/="},
                {Tokens::mod_assign, "%="},

                {Tokens::add, "+"},
                {Tokens::sub, "-"},
                {Tokens::mul, "*"},
                {Tokens::div, "/"},
                {Tokens::mod, "%"},
                {Tokens::assign, "="},

                {Tokens::endline, "\n"}
			};

            inline bool is_keyword() const { return std::holds_alternative<Tokens>(_value); }
            inline bool is_number() const { return std::holds_alternative<double>(_value); }
            inline bool is_boolean() const { return std::holds_alternative<bool>(_value); }
            inline bool is_identifier() const { return std::holds_alternative<identifier>(_value); }
            inline bool is_eof() const { return std::holds_alternative<eof>(_value); }

            inline Tokens get_token() const { return std::get<Tokens>(_value); }
            inline const identifier& get_identifier() const { return std::get<identifier>(_value); }
            inline double get_number() const { return std::get<double>(_value); }
            inline bool get_boolean() const { return std::get<bool>(_value); }
            inline const token_value& get_value() const { return _value; }
        
            inline size_t get_line_number() const noexcept { return _line; }

	        inline bool has_value(token_value value) const noexcept { return _value == std::move(value); }

        private:
            token_value _value;
            unsigned int _line = 0;
    };

}

namespace std
{
    inline std::string to_string(Ak::Kl::Tokens t) { return Ak::Kl::Token::kw_tokens.has(t) ? std::move(std::string(Ak::Kl::Token::kw_tokens[t])) : std::move(std::string(Ak::Kl::Token::operators_token[t])); }

    inline std::string to_string(const Ak::Kl::token_value& t)
    {
        return std::visit(Ak::overloaded
        {
            [](Ak::Kl::Tokens rt) { return to_string(rt); },
            [](double d) { return to_string(d); },
            [](bool d) { return to_string(d); },
            [](const std::string& str) { return str; },
            [](const Ak::Kl::identifier& id) { return id.name; },
            [](Ak::Kl::eof) { return std::string("<EOF>"); }
        }, t);
    }
}

#endif // __AK_KILA_TOKENS__
