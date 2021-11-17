// This file is a part of Akel
// CREATED : 17/11/2021
// UPDATED : 17/11/2021

#include <Utils/Containers/bst.h>
#include <Core/core.h>

namespace Ak
{
    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(T data)
    {
        _data = data;
    }

    template <typename T>
    BinarySearchTree* BinarySearchTree<T>::add(T data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
                _right = _right->add(data);
            else
                _right = custom_malloc<BinarySearchTree<T>>(data);
        }
        else
        {
            if(_left != nullptr)
                _left = _left->add(data);
            else
                _left = custom_malloc<BinarySearchTree<T>>(data);
        }
    }

    template <typename T>
    BinarySearchTree* BinarySearchTree<T>::remove(T data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
                _right = _right->remove(data);
            else
                return nullptr;
        }
        else if(data < _data)
        {
            if(_left != nullptr)
                _left = _left->remove(data);
            else
                return nullptr;
        }
        else
        {
            if(_left == nullptr && _right == nullptr)
            {
                custom_free(this);
                return nullptr;
            }
            else if(_left == nullptr || _right == nullptr)
            {
                BinarySearchTree<T>* temp;
                if(_left == nullptr)
                    temp = _right;
                else
                    temp = _left;
                custom_free(this);
                return temp;
            }
            else
            {
                BinarySearchTree<T>* temp = _right->find_minimum();
                _data = temp->getData();
                _right = _right->remove(temp->getData());
            }
        }
        return this;
    }

    template <typename T>
    BinarySearchTree* BinarySearchTree<T>::find_minimum()
    {
        if(_left != nullptr) // node with minimum value will have no left child
            return _left->find_minimum(); // left most element will be minimum
        return this;
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        if(_left != nullptr)
            custom_free(_left);
        if(_right != nullptr)
            custom_free(_right);
    }
}
