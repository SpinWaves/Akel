// This file is a part of Akel
// CREATED : 11/11/2021
// UPDATED : 12/11/2021

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
        punct
    };

    char_type get_char_type(int c)
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
        size_t index = stream.getindex();

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
        
        if(std::optional<Tokens> t  = get_keyword(word))
            return Token(*t, line, index);
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
                    {
                        size_t remaining = word.size() - (endptr - word.c_str());
                        unexpected_error(endptr, stream.getline(), stream.getindex() - remaining).expose();
                    }
                }
                return Token(num, line, index);
            } 
            return Token(identifier{std::move(word)}, line, index);
        }
    }
    
    Token fetch_operator(StreamStack& stream)
    {
        size_t line = stream.getline();
        size_t index = stream.getindex();

        if(std::optional<Tokens> t = get_operator(stream))
            return Token(*t, line, index);
        else
        {
            std::string unexpected;
            unsigned int err_line_number = stream.getline();
            unsigned int err_char_index = stream.getindex();
            for(int c = stream(); get_char_type(c) == char_type::punct; c = stream())
            {
                unexpected.push_back(char(c));
            }
            unexpected_error(unexpected.c_str(), err_line_number, err_char_index).expose();
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
        do
        {
            c = stream();
            if(closing && c == '/')
                return;
            closing = (c == '*');
        } while(get_char_type(c) != char_type::eof);

        stream.push_back(c);
        no_end("'*/'", stream.getline(), stream.getindex()).expose();
    }

    Token lexe(StreamStack& stream)
    {
        while(true)
        {
            size_t line = stream.getline();
            size_t index = stream.getindex();
            int c = stream();

            switch(get_char_type(c))
            {
                case char_type::eof:  return {eof(), line, index};
                
                case char_type::space: continue;
                
                case char_type::alphanum: stream.push_back(c); return fetch_word(stream);
                
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
