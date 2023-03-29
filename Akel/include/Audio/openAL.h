// This file is a part of Akel
// Authors : @kbz_8
// Created : 03/08/2021
// Updated : 29/03/2023

#ifndef __AK_OPENAL__
#define __AK_OPENAL__

#include <Akpch.h>
#include <Core/core.h>

namespace Ak
{
	inline void checkAl(int32_t result, const char* function)
	{
		if(result == AL_NO_ERROR)
			return;
		std::string failure;
		switch(result)
		{
			case AL_NO_ERROR:			failure = "Success"; break;
			case AL_INVALID_NAME:		failure = "Invalid name"; break;
			case AL_INVALID_ENUM:		failure = "Invalid enum"; break;
			case AL_INVALID_VALUE:		failure = "Invalid value"; break;
			case AL_INVALID_OPERATION:	failure = "Invalid operation"; break;
			case AL_OUT_OF_MEMORY:		failure = "A memory allocation failed"; break;

			default:					failure = "ERROR: UNKNOWN AL ERROR"; break;
		}
		Core::log::report(ERROR, "OpenAL : %s in %s", failure.c_str(), function);
	}

    class OpenAL
    {
        public:
            OpenAL();

            bool initOAL();
            void shutdownOAL();

            ~OpenAL();

        private:
			struct _Pimpl;
			_Pimpl* _impl = nullptr;
    };

	#undef checkAl
	#define checkAl(res) checkAl(res, AK_FUNC_SIG)
}

#endif // __AK_OPENAL__
