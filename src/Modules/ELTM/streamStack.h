// This file is a part of AtlasEngine
// CREATED : 07/05/2021
// UPDATED : 08/05/2021

#ifndef __STREAM_STACK__
#define __STREAM_STACK__

#include <AEpch.h>
#include <Modules/ELTM/token.h>

namespace AE
{
	class StreamStack
	{
		public:
			void tokenize(const char* file);
			Token getToken(int line, int index);

		private:
			std::vector<Token> _tokens;
	};
}

#endif // __STREAM_STACK__

