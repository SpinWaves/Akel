// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/05/2022
// Updated : 16/05/2022

#ifndef __AK_KILA_EXPRESSIONS__
#define __AK_KILA_EXPRESSIONS__

#include <Akpch.h>
#include "types.h"

namespace Ak::Kl
{
    template <typename R>
    class expression
    {
        public:
            using ptr = std::unique_ptr<const expression>;

            virtual R evaluate() const = 0;
            virtual ~expression() = default;

        protected:
            expression() = default;

        private:
            expression(const expression&) = delete;
            void operator=(const expression&) = delete;
    };
}

#endif // __AK_KILA_EXPRESSIONS__
