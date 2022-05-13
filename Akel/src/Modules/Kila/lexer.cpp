// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 13/05/2022

#include <Modules/Kila/lexer.h>
#include <Modules/Kila/errors.h>
#include <Modules/Kila/warnings.h>
#include <Modules/Kila/file.h>

namespace Ak::Kl
{
    enum class char_type
    {
        eof,
        space,
        alphanum,
        punct
    };

    char_type get_char_type(char c)
    {
        if(c < 0)
            return char_type::eof;
        if(std::isspace(c))
            return char_type::space;
        if(std::isalpha(c) || std::isdigit(c) || char(c) == '_')
            return char_type::alphanum;
        return char_type::punct;
    }

    Token fetch_word(StreamStack& stream)
    {
        size_t line = stream.getline();
        std::string word;
        char c = stream();
        bool is_number = std::isdigit(c);
        
        do
        {
            word.push_back(char(c));
            c = stream();
            
            if(c == '.' && word.back() == '.')
            {
                stream.push_back(word.back());
                word.pop_back();
                break;
            }
        } while(get_char_type(c) == char_type::alphanum || (is_number && c == '.'));
        
        stream.push_back(c);
        
        if(std::optional<Tokens> t = get_keyword(word))
        {
            if(t->has_value(Tokens::b_true))
                return Token(true, line);
            if(t->has_value(Tokens::b_false))
                return Token(false, line);
            return Token(*t, line);
        }
        if(std::isdigit(word.front()))
        {
            if(word.find('.') != std::string::npos)
                return Token(std::stod(word), line);
            return Token(std::stoll(word), line);
        }
        return Token(identifier{std::move(word)}, line);
    }
    
    Token fetch_operator(StreamStack& stream)
    {
        size_t line = stream.getline();

        if(std::optional<Tokens> t = get_operator(stream))
            return Token(*t, line);
        std::string unexpected;
        unsigned int err_line_number = stream.getline();
        for(int c = stream(); get_char_type(c) == char_type::punct; c = stream())
            unexpected.push_back(char(c));
        unexpected_error(unexpected.c_str(), err_line_number).expose();
    }

    void skip_line_comment(StreamStack& stream)
    {
        char c = 0;
        do
        {
            c = stream();
        } while(c != '\n' && get_char_type(c) != char_type::eof);
        
        if(c != '\n')
            stream.push_back(c);
    }
    
    void skip_block_comment(StreamStack& stream)
    {
        char c = 0;
        int line = stream.getline();
        do
        {
            c = stream();
            if(c == ']' && stream() == ']')
                return;
        } while(get_char_type(c) != char_type::eof);

        stream.push_back(c);
        no_end("]]", line).expose();
    }

    Token lexe(StreamStack& stream)
    {
        while(true)
        {
            size_t line = stream.getline();
            char c = stream();

            switch(get_char_type(c))
            {
                case char_type::eof:  return {eof(), line};
                case char_type::space: continue;
                case char_type::alphanum: stream.push_back(c); return fetch_word(stream);
                case char_type::punct:
                {
                    switch(c)
                    {
                        case '-':
                        {
                            char c1 = stream();
                            if(c1 == '-')
                            {
                                c1 = stream();
                                if(c1 == '[' && stream() == '[')
                                    skip_block_comment(stream);
                                else
                                    skip_line_comment(stream);
                                continue;
                            }
                            else
                                stream.push_back(c1);
                        }

                        default: stream.push_back(c); return fetch_operator(stream);
                    }
                    break;
                }
            }
        }
    }
}
