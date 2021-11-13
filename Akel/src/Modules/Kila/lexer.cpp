// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 13/11/2021

#include <Modules/Kila/lexer.h>
#include <Modules/Kila/errors.h>
#include <Modules/Kila/warnings.h>

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

    static std::map<std::string, std::string> __set_macros;

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
        std::string identifier;
        std::vector<Token> cache;
        int c = stream();
        while(c != '\n')
        {
            do
            {
                identifier.push_back(char(c));
                c = stream();
            } while(get_char_type(c) == char_type::alphanum && get_char_type(c) != char_type::space && c != '\n');
            
            if(get_char_type(c) == char_type::space && c != '\n')
                stream.push_back(c);
            
            if(std::optional<Macro_Tokens> t = get_macro(identifier))
                cache.push_back(Token(macro{*t}, line));
            else if(cache.empty())
                unexpected_macro_error(identifier.c_str(), line).expose();
            else
                cache.push_back(fetch_word(identifier));
        }

        switch(cache.get_value())
        {
            f
        };
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
        do
        {
            c = stream();
            if(closing && c == '/')
                return;
            closing = (c == '*');
        } while(get_char_type(c) != char_type::eof);

        stream.push_back(c);
        no_end("'*/'", stream.getline()).expose();
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
