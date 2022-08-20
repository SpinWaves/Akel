// This file is a part of Akel
// Authors : @kbz_8
// Created : 20/08/2022
// Updated : 20/08/2022

#ifndef __AK_ASSERT__
#define __AK_ASSERT__

#ifdef AK_RELEASE
    #define assert(con) (void)(0)
    #define Ak_assert(con, msg) (void)(0)
#else
    namespace Ak { void FatalError(std::string message, ...); }
    #define Ak_assert(con, msg) if(!bool(con)) Ak::FatalError("Assertion failed with message : %s", msg)
#endif

#endif // __AK_ASSERT__
