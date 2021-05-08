// This file is a part of AtlasEngine
// CREATED : 07/05/2021
// UPDATED : 08/05/2021

#ifndef __STREAM_STACK__
#define __STREAM_STACK__

#include <AEpch.h>
#include <Modules/eltm/token.h>

namespace AE
{
	class StreamStack
	{
		public:
			StreamStack();
			void tokenize(const char* file);

		private:
			std::vector<Token> _tokens;
	};
}

#endif // __STREAM_STACK__

