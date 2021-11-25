// This file is a part of Akel
// CREATED : 17/11/2021
// UPDATED : 25/11/2021

#include <Utils/Containers/bst.h>
#include <Core/core.h>

namespace Ak
{
    template <typename T = void, typename ... Args>
    T* custom_malloc(Args&& ... args);
    template <typename T = void>
    void custom_free(T* ptr);

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(T&& data)
    {
        _data = std::forward<T>(data);
    }

    template <typename T>
    void BinarySearchTree<T>::add(T&& data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
                _right->add(std::forward<T>(data));
            else
                _right = custom_malloc<BinarySearchTree<T>>(std::forward<T>(data));
        }
        else
        {
            if(_left != nullptr)
                _left->add(std::forward<T>(data));
            else
                _left = custom_malloc<BinarySearchTree<T>>(std::forward<T>(data));
        }
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::remove(T&& data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
                _right = _right->remove(std::forward<T>(data));
            else
                return nullptr;
        }
        else if(data < _data)
        {
            if(_left != nullptr)
                _left = _left->remove(std::forward<T>(data));
            else
                return nullptr;
        }
        else
        {
            if(_left == nullptr && _right == nullptr) // no children
            {
                custom_free(this);
                return nullptr;
            }
            else if(_left == nullptr || _right == nullptr) // one child
            {
                BinarySearchTree<T>* temp;
                if(_left == nullptr)
                    temp = _right;
                else
                    temp = _left;
                custom_free(this);
                return temp;
            }
            else // two children
            {
                BinarySearchTree<T>* temp = _right->find_minimum();
                _data = temp->getData();
                _right = _right->remove(std::forward<T>(temp->getData()));
            }
        }
        return this;
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::find_minimum()
    {
        if(_left != nullptr) // node with minimum value will have no left child
            return _left->find_minimum(); // left most element will be minimum
        return this;
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::find(T&& data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
                _right->find(std::forward<T>(data));
            else
                return nullptr;
        }
        else if(data < _data)
        {
            if(_left != nullptr)
                _left->find(std::forward<T>(data));
            else
                return nullptr;
        }
        else
            return this;
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::find_parent(T&& data)
    {
        if(data > _data)
        {
            if(_right != nullptr)
            {
                if(_right->getData() == data)
                    return this;
                _right->find_parent(std::forward<T>(data));
            }
            else
                return nullptr;
        }
        else if(data < _data)
        {
            if(_left != nullptr)
            {
                if(_left->getData() == data)
                    return this;
                _left->find_parent(std::forward<T>(data));
            }
            else
                return nullptr;
        }
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        std::cout << _data << std::endl;
        if(_left != nullptr)
            custom_free(_left);
        if(_right != nullptr)
            custom_free(_right);
    }
}
