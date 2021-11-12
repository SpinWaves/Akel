// This file is a part of Akel
// CREATED : 08/11/2021
// UPDATED : 12/11/2021

#ifndef __AK_KILA_TOKENS__
#define __AK_KILA_TOKENS__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>
#include <Modules/Kila/stream_stack.h>

namespace Ak::Kl
{
    enum class Tokens
    {
        kw_fn,
        kw_class,
        kw_public,
        kw_private,
        kw_struct,
        kw_mtd,
        kw_var,
        kw_obj,
        kw_switch,
        kw_case,
		kw_default,
        kw_for,
		kw_while,
		kw_do,
		kw_break,
		kw_continue,
		kw_return,
        kw_entry,
        kw_newtype,
        kw_uniform,

        end_line,
        type_specifier,
        brecket_b,
        brecket_e,
        embrace_b,
        embrace_e,
        comma,
        dot,
        square_b,
        square_e,

        t_int,
        t_float,
        t_double,
        t_bool,
        t_byte,
        t_unsigned,

        macro,
        m_set,
        m_unset,
        m_get,
        m_once,
        m_endif,
        m_vert,
        m_frag,
        m_global,

        statment_if,
        statment_else,
        statment_elif,

        inc,
		dec,
		
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

        question,
        logical_not,
        logical_and,
        logical_or
    };
    
    struct eof{};
    struct identifier { std::string name; };

    std::optional<Tokens> get_keyword(const std::string& word);
	std::optional<Tokens> get_operator(StreamStack& stream);

    using token_value = std::variant<Tokens, identifier, double, eof>;

    class Token
    {
        public:
            Token(token_value value, unsigned int line, unsigned int index);

			static inline duets_array<Tokens, std::string> kw_tokens
			{
                {Tokens::kw_fn, "fn"},
                {Tokens::kw_class, "class"},
                {Tokens::kw_public, "public"},
                {Tokens::kw_private, "private"},
                {Tokens::kw_struct, "struct"},
                {Tokens::kw_mtd, "mtd"},
                {Tokens::kw_var, "var"},
                {Tokens::kw_obj, "obj"},
                {Tokens::kw_switch, "switch"},
                {Tokens::kw_case, "case"},
                {Tokens::kw_default, "default"},
                {Tokens::kw_for, "for"},
                {Tokens::kw_while, "while"},
                {Tokens::kw_do, "do"},
                {Tokens::kw_break, "break"},
                {Tokens::kw_continue, "continue"},
                {Tokens::kw_return, "return"},
                {Tokens::kw_entry, "entry"},
                {Tokens::kw_newtype, "newtype"},
                {Tokens::kw_uniform, "uniform"},

                {Tokens::t_int, "int"},
                {Tokens::t_float, "float"},
                {Tokens::t_double, "double"},
                {Tokens::t_bool, "bool"},
                {Tokens::t_byte, "byte"},
                {Tokens::t_unsigned, "unsigned"},

                {Tokens::m_set, "set"},
                {Tokens::m_unset, "unset"},
                {Tokens::m_get, "get"},
                {Tokens::m_once, "once"},
                {Tokens::m_endif, "endif"},
                {Tokens::m_vert, "vert"},
                {Tokens::m_frag, "frag"},
                {Tokens::m_global, "global"},

                {Tokens::statment_if, "if"},
                {Tokens::statment_else, "else"},
                {Tokens::statment_elif, "elif"}
			};

			static inline duets_array<Tokens, std::string> operators_token
			{
                {Tokens::end_line, ";"},
                {Tokens::comma, ","},
                {Tokens::dot, "."},
                {Tokens::type_specifier, ":"},
                {Tokens::brecket_b, "("},
                {Tokens::brecket_e, ")"},
                {Tokens::embrace_b, "{"},
                {Tokens::embrace_e, "}"},
                {Tokens::square_b, "["},
                {Tokens::square_e, "]"},

                {Tokens::eq, "=="},
                {Tokens::ne, "!="},
                {Tokens::lt, "<"},
                {Tokens::gt, ">"},
                {Tokens::le, "<="},
                {Tokens::ge, ">="},

                {Tokens::question, "?"},
                {Tokens::logical_not, "!"},
                {Tokens::logical_and, "&&"},
                {Tokens::logical_or, "||"},

                {Tokens::macro, "@"},

                {Tokens::inc, "++"},
                {Tokens::dec, "--"},

                {Tokens::add, "+"},
                {Tokens::sub, "-"},
                {Tokens::mul, "*"},
                {Tokens::div, "/"},
                {Tokens::mod, "%"},
                {Tokens::assign, "="}
			};

            inline bool is_keyword() const { return std::holds_alternative<Tokens>(_value); }
            inline bool is_number() const { return std::holds_alternative<double>(_value); }
            inline bool is_identifier() const { return std::holds_alternative<identifier>(_value); }
            inline bool is_eof() const { return std::holds_alternative<eof>(_value); }

            inline Tokens get_token() const { return std::get<Tokens>(_value); }
            inline const identifier& get_identifier() const { return std::get<identifier>(_value); }
            inline double get_number() const { return std::get<double>(_value); }
            inline const token_value& get_value() const { return _value; }
        
            inline size_t get_line_number() const noexcept { return _line; }
            inline size_t get_char_index() const noexcept { return _index; }

	        bool has_value(token_value value) const { return _value == std::move(value); }

        private:
            token_value _value;
            unsigned int _line = 0;
            unsigned int _index = 0;
    };
}

#endif // __AK_KToken::ILA_TOKENS__
