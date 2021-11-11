// This file is a part of Akel
// CREATED : 09/11/2021
// UPDATED : 11/11/2021

#ifndef __AK_KILA_LEXER__
#define __AK_KILA_LEXER__

#include <Akpch.h>
#include <Modules/Kila/tokens.h>
#include <Modules/Kila/stream_stack.h>

namespace Ak::Kl
{
    Token lexe(StreamStack& stream);
}

#endif // __AK_KILA_LEXER__
