// This file is a part of Akel
// Authors : @kbz_8
// Created : 11/11/2021
// Updated : 25/02/2022

#include <Modules/Kila/lexer.h>
#include <Modules/Kila/errors.h>
#include <Modules/Kila/warnings.h>
#include <Modules/Kila/macros.h>
#include <Modules/Kila/file.h>

namespace Ak::Kl
{
    enum class char_type
    {
        eof,
        space,
        alphanum,
        punct,
        macro
    };

    char_type get_char_type(int c)
    {
        if(c < 0)
            return char_type::eof;
        if(std::isspace(c))
            return char_type::space;
        if(std::isalpha(c) || std::isdigit(c) || char(c) == '_')
            return char_type::alphanum;
        if(c == (int)Token::macros_token[Macro_Tokens::macro][0])
            return char_type::macro;
        return char_type::punct;
    }

    Token fetch_word(StreamStack& stream)
    {
        size_t line = stream.getline();

        std::string word;
        
        int c = stream();
        
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
        
        if(Macros::get_sets().count(word))
            word = Macros::get_sets()[word];

        stream.push_back(c);
        
        if(std::optional<Tokens> t = get_keyword(word))
            return Token(*t, line);
        else
        {
            if(std::isdigit(word.front()))
            {
                char* endptr;
                double num = strtol(word.c_str(), &endptr, 0);
                if(*endptr != 0)
                {
                    num = strtod(word.c_str(), &endptr);
                    if(*endptr != 0)
                        unexpected_error(endptr, stream.getline()).expose();
                }
                return Token(num, line);
            } 
            return Token(identifier{std::move(word)}, line);
        }
    }
    
    Token fetch_operator(StreamStack& stream)
    {
        size_t line = stream.getline();

        if(std::optional<Tokens> t = get_operator(stream))
            return Token(*t, line);
        else
        {
            std::string unexpected;
            unsigned int err_line_number = stream.getline();
            for(int c = stream(); get_char_type(c) == char_type::punct; c = stream())
            {
                unexpected.push_back(char(c));
            }
            unexpected_error(unexpected.c_str(), err_line_number).expose();
        }
    }

    void fetch_macro(StreamStack& stream)
    {
        size_t line = stream.getline();
        std::vector<std::string> identifiers;
        identifiers.push_back("");
        std::vector<Token> cache;
        int c = stream();
        std::optional<Macro_Tokens> t;

        do
        {
            identifiers.back().push_back(char(c));
            c = stream();
            if(get_char_type(c) == char_type::space)
            {
                c = stream();
                if(t = get_macro(identifiers.back()))
                    cache.push_back(Token(*t, line));
                else if(cache.empty())
                    unexpected_macro_error(identifiers.back().c_str(), line).expose();
                identifiers.push_back("");
            }
        } while(c != '\n' && get_char_type(c) != char_type::eof && get_char_type(c) != char_type::macro);
        
        if(c != '\n')
            stream.push_back(c);

        switch(cache.front().get_macro())
        {
            case Macro_Tokens::entry:
            {
                if(t = get_macro(identifiers[1]))
                {
                    switch(*t)
                    {
                        case Macro_Tokens::vert: Macros::set_entry(entries::vert); break;
                        case Macro_Tokens::frag: Macros::set_entry(entries::frag); break;
                        case Macro_Tokens::global: Macros::set_entry(entries::global); break;

                        default: unexpected_macro_error(identifiers[1].c_str(), line).expose(); break;
                    }
                }
                else
                    unexpected_macro_error(identifiers[1].c_str(), line).expose();
                break;
            }

            case Macro_Tokens::set : Macros::new_set(identifiers[1], identifiers[2]); break;
            case Macro_Tokens::unset : Macros::remove_set(identifiers[1]); break;

            case Macro_Tokens::getonce : break;
            
            case Macro_Tokens::get :
            {
                if(!Macros::have_once(identifiers[1]))
                {
                    File f(std::string(Core::getMainDirPath() + "Tests/Kila/" + identifiers[1]).c_str()); // Path for tests (will change)
                    stream.add_file(f.get_path());
                    std::stack<int> temp;
                    while(!f.is_eof())
                    {
                        temp.push(f());
                    }
                    temp.pop(); // To remove the end of file
                    while(!temp.empty())
                    {
                        stream.push_back(temp.top());
                        temp.pop();
                    }
                }
                break;
            }
        }
    }
    
    void skip_line_comment(StreamStack& stream)
    {
        int c = 0;
        do
        {
            c = stream();
        } while(c != '\n' && get_char_type(c) != char_type::eof);
        
        if(c != '\n')
            stream.push_back(c);
    }
    
    void skip_block_comment(StreamStack& stream)
    {
        bool closing = false;
        int c = 0;
        int line = stream.getline();
        do
        {
            c = stream();
            if(closing && c == '/')
                return;
            closing = (c == '*');
        } while(get_char_type(c) != char_type::eof);

        stream.push_back(c);
        no_end("'*/'", line).expose();
    }

    Token lexe(StreamStack& stream)
    {
        while(true)
        {
            size_t line = stream.getline();
            int c = stream();

            switch(get_char_type(c))
            {
                case char_type::eof:  return {eof(), line};
                
                case char_type::space: continue;
                
                case char_type::alphanum: stream.push_back(c); return fetch_word(stream);

                case char_type::macro: fetch_macro(stream); continue;
                
                case char_type::punct:
                {
                    switch(c)
                    {
                        case '/':
                        {
                            char c1 = stream();
                            switch(c1)
                            {
                                case '/': skip_line_comment(stream); continue;
                                
                                case '*': skip_block_comment(stream); continue;
                                
                                default: stream.push_back(c1);
                            }
                        }

                        default: stream.push_back(c); return fetch_operator(stream);
                    }
                }
                break;
            }
        }
    }
}
