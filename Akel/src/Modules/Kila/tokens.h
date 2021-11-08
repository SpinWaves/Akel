// This file is a part of Akel
// CREATED : 08/11/2021
// UPDATED : 08/11/2021

#ifndef __AK_KILA_TOKENS__
#define __AK_KILA_TOKENS__

#include <Akpch.h>
#include <Utils/Containers/duetsArray.h>

namespace Ak::Kl
{
    enum class Tokens
    {
        kw_fn,
        kw_class,
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

        end_line,
        type_specifier,
        brecket_b,
        brecket_e,
        embrace_b,
        embrace_e,

        t_int,
        t_float,
        t_double,
        t_bool,
        t_string,
        t_byte,
        t_unsigned,

        macro,
        m_set,
        m_unset,
        m_get,
        m_once,
        m_if,
        m_elif,
        m_else,
        m_endif,

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
        assign
    };
    
    struct eof{};
    struct identifier { const char* name; };

    using token_value = std::variant<Tokens, identifier, double, std::string, eof>;

    class Token
    {
        public:
            Tokens(token_value value, unsigned int line, unsigned int index);

			static inline duets_array<eltm_token, std::string> kw_tokens
			{
                {Token::kw_fn, "fn"},
                {Token::kw_class, "class"},
                {Token::kw_struct, "struct"},
                {Token::kw_mtd, "mtd"},
                {Token::kw_var, "var"},
                {Token::kw_obj, "obj"},
                {Token::kw_switch, "switch"},
                {Token::kw_case, "case"},
                {Token::kw_default, "default"},
                {Token::kw_for, "for"},
                {Token::kw_while, "while"},
                {Token::kw_do, "do"},
                {Token::kw_break, "break"},
                {Token::kw_continue, "continue"},
                {Token::kw_return, "return"},

                {Token::t_int, "int"},
                {Token::t_float, "float"},
                {Token::t_double, "double"},
                {Token::t_bool, "bool"},
                {Token::t_string, "string"},
                {Token::t_byte, "byte"},
                {Token::t_unsigned, "unsigned"},

                {Token::m_set, "set"},
                {Token::m_unset, "unset"},
                {Token::m_get, "get"},
                {Token::m_once, "once"},
                {Token::m_endif, "endif"},

                {Token::statment_if, "if"},
                {Token::statment_else, "else"},
                {Token::statment_elif, "elif"}
			};

			static inline duets_array<Tokens, std::string> mixable_kw_token
			{
                {Token::end_line, ";"},
                {Token::type_specifier, ":"},
                {Token::brecket_b, "("},
                {Token::brecket_e, ")"},
                {Token::embrace_b, "{"},
                {Token::embrace_e, "}"},

                {Token::macro, "@"},

                {Token::inc, "++"},
                {Token::dec, "--"},

                {Token::add, "+"},
                {Token::sub, "-"},
                {Token::mul, "*"},
                {Token::div, "/"},
                {Token::mod, "%"},
                {Token::assign, "="}
			};

            bool is_keyword() const;
            bool is_string() const;
            bool is_number() const;
            bool is_identifier() const;
            bool is_eof() const;

            Tokens get_reserved_token() const;
            const identifier& get_identifier() const;
            double get_number() const;
            const std::string& get_string() const;
            const token_value& get_value() const;
            
            size_t get_line_number() const;
            size_t get_char_index() const;

            bool has_value(token_value value) const;

        private:
            Tokens _value;
            unsigned int _line = 0;
            unsigned int _index = 0;
    };
}

#endif // __AK_KToken::ILA_TOKENS__
