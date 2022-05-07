// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/11/2021
// Updated : 07/05/2022

#ifndef __AK_KILA_TOKENS__
#define __AK_KILA_TOKENS__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>
#include <Modules/Kila/stream_stack.h>

namespace Ak::Kl
{
    enum class Tokens
    {
        kw_function,
        kw_end,
        kw_for,
		kw_while,
		kw_do,
		kw_break,
		kw_continue,
		kw_return,
        kw_location,
        kw_uniform,

        type_specifier,
        bracket_b,
        bracket_e,
        embrace_b,
        embrace_e,
        comma,
        dot,
        square_b,
        square_e,

        t_void,
        
        t_i8
        t_i16
        t_i32,
        t_i64,

        t_f32,
        t_f64
        
        t_bool,
        
        t_unsigned,
        
        t_vec2,
        t_vec3,
        t_vec4,
        t_mat2,
        t_mat3,
        t_mat4,

        statment_if,
        statment_else,
        statment_elif,

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

        ret_type,

        logical_not,
        logical_and,
        logical_or
    };

    struct eof{};
    struct identifier { std::string name; };

    std::optional<Tokens> get_keyword(const std::string& word);
	std::optional<Tokens> get_operator(StreamStack& stream);

	inline bool operator==(const identifier& id1, const identifier& id2) { return id1.name == id2.name; }
	inline bool operator!=(const identifier& id1, const identifier& id2) { return id1.name != id2.name; }
	inline constexpr bool operator==(const eof&, const eof&) noexcept { return true; }
	inline constexpr bool operator!=(const eof&, const eof&) noexcept { return false; }

    using token_value = std::variant<Tokens, identifier, double, long long, eof>;

    class Token
    {
        public:
            Token(token_value value, unsigned int line);

			static inline duets_array<Tokens, std::string> kw_tokens
			{
                {Tokens::kw_function, "function"},
                {Tokens::kw_end, "end"},
                {Tokens::kw_for, "for"},
                {Tokens::kw_while, "while"},
                {Tokens::kw_do, "do"},
                {Tokens::kw_break, "break"},
                {Tokens::kw_continue, "continue"},
                {Tokens::kw_return, "return"},
                {Tokens::kw_location, "location"},
                {Tokens::kw_uniform, "uniform"},

                {Tokens::t_void, "void"},
                {Tokens::t_int, "int"},
                {Tokens::t_float, "float"},
                {Tokens::t_bool, "bool"},
                {Tokens::t_unsigned, "unsigned"},
                {Tokens::t_vec2, "vec2"},
                {Tokens::t_vec3, "vec3"},
                {Tokens::t_vec4, "vec4"},
                {Tokens::t_mat2, "mat2"},
                {Tokens::t_mat3, "mat3"},
                {Tokens::t_mat4, "mat4"},

                {Tokens::statment_if, "if"},
                {Tokens::statment_else, "else"},
                {Tokens::statment_elif, "elif"}
			};

			static inline duets_array<Tokens, std::string> operators_token
			{
                {Tokens::comma, ","},
                {Tokens::dot, "."},
                {Tokens::type_specifier, ":"},
                {Tokens::bracket_b, "("},
                {Tokens::bracket_e, ")"},
                {Tokens::embrace_b, "{"},
                {Tokens::embrace_e, "}"},
                {Tokens::square_b, "["},
                {Tokens::square_e, "]"},

                {Tokens::ret_type, "->"},

                {Tokens::eq, "=="},
                {Tokens::ne, "!="},
                {Tokens::lt, "<"},
                {Tokens::gt, ">"},
                {Tokens::le, "<="},
                {Tokens::ge, ">="},

                {Tokens::logical_not, "not"},
                {Tokens::logical_and, "and"},
                {Tokens::logical_or, "or"},

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
			};

            inline bool is_keyword() const { return std::holds_alternative<Tokens>(_value); }
            inline bool is_double() const { return std::holds_alternative<double>(_value); }
            inline bool is_int() const { return std::holds_alternative<int>(_value); }
            inline bool is_float() const { return std::holds_alternative<float>(_value); }
            inline bool is_identifier() const { return std::holds_alternative<identifier>(_value); }
            inline bool is_eof() const { return std::holds_alternative<eof>(_value); }

            inline Tokens get_token() const { return std::get<Tokens>(_value); }
            inline const identifier& get_identifier() const { return std::get<identifier>(_value); }
            inline double get_double() const { return std::get<double>(_value); }
            inline double get_int() const { return std::get<int>(_value); }
            inline double get_float() const { return std::get<float>(_value); }
            inline const token_value& get_value() const { return _value; }
        
            inline size_t get_line_number() const noexcept { return _line; }

	        bool has_value(token_value value) const { return _value == std::move(value); }

        private:
            token_value _value;
            unsigned int _line = 0;
    };
}

#endif // __AK_KILA_TOKENS__
