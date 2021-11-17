// This file is a part of Akel
// CREATED : 17/11/2021
// UPDATED : 17/11/2021

#ifndef __AK_BINARY_SEARCH_TREE__
#define __AK_BINARY_SEARCH_TREE__

namespace Ak
{
    template <typename T>
    class BinarySearchTree
    {
        public:
            explicit BinarySearchTree(T data);
            BinarySearchTree* add(T data); // The type returned is for internal recursion
            BinarySearchTree* remove(T data); // Same shit
            BinarySearchTree* find_minimum();
            inline T& getData() { return _data; }
            ~BinarySearchTree();
        
        private:
            T _data;
            BinarySearchTree* _left = nullptr;
            BinarySearchTree* _right = nullptr;
    };
}

#include <Utils/Containers/bst.inl>

#endif // __AK_BINARY_SEARCH_TREE__
