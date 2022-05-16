// This file is a part of Akel
// Authors : @kbz_8
// Created : 16/05/2022
// Updated : 16/05/2022

#include "expressions.h"
#include "node.h"
#include "node_parser.h"
#include "errors.h"
#include "token_iterator.h"
#include "compiler_context.h"

namespace Ak::Kl
{
    template <typename R, typename T>
    class global_variable_expression: public expression<R>
    {
        public:
            global_variable_expression(int idx) : _idx(idx) {}              
            R evaluate() const override
            {
            }

        private:
            int _idx;
    };

    template <typename R, typename T>
    class local_variable_expression: public expression<R>
    {
        public:
            local_variable_expression(int idx) : _idx(idx) {}
            R evaluate() const override
            {
            }

        private:
            int _idx;
    };

    template<typename R>
    class function_expression: public expression<R>
    {
        public:
            function_expression(int idx) : _idx(idx) {}
            R evaluate() const override {}

        private:
            int _idx;
    };
}
