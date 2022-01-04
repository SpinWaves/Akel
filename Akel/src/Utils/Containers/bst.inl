// This file is a part of Akel
// CREATED : 17/11/2021
// UPDATED : 04/01/2022

#include <Utils/Containers/bst.h>

namespace Ak
{
    void Error(std::string message);

    template <typename T = void, typename ... Args>
    T* custom_malloc(Args&& ... args);
    template <typename T = void>
    void custom_free(T* ptr);

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(T&& data) : _data(std::forward<T>(data)), _is_init(true) {}

    template <typename T>
    void BinarySearchTree<T>::add(T&& data)
    {
        if(!_is_init)
        {
            _data = std::forward<T>(data);
            return;
        }
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
    void BinarySearchTree<T>::add(BinarySearchTree<T>* node)
    {
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to add element (NULL node)");
            return;
        }
        if(!_is_init)
        {
            if(node->has_data())
                _data = node->getData();
            else
                Error("Binary Search Tree : unable to add element (no data)");
            return;
        }
        if(node->getData() > _data)
        {
            if(_right != nullptr)
                _right->add(node);
            else
                _right = node;
        }
        else
        {
            if(_left != nullptr)
                _left->add(node);
            else
                _left = node;
        }
    }

    template <typename T>
    void BinarySearchTree<T>::remove(T&& data)
    {
        BinarySearchTree<T>* node = find(std::forward<T>(data));
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to remove element (no node found with this value)");
            return;
        }
        if(node->getLeft() == nullptr && node->getRight() == nullptr) // no children
        {
            custom_free(node);
            return;
        }
        else if(node->getLeft() == nullptr || node->getRight() == nullptr) // only one child
        {
            BinarySearchTree<T>* parent = find_parent(node);
            if(node->getLeft() == nullptr)
            {
                if(parent->getLeft() == node)
                {
                    parent->setLeft(node->getRight());
                    node->setRight(nullptr);
                    custom_free(node);
                    return;
                }
                else
                {
                    parent->setRight(node->getRight());
                    node->setRight(nullptr);
                    custom_free(node);
                    return;
                }
            }
            else
            {
                if(parent->getRight() == node)
                {
                    parent->setRight(node->getLeft());
                    node->setLeft(nullptr);
                    custom_free(node);
                    return;
                }
                else
                {
                    parent->setLeft(node->getLeft());
                    node->setRight(nullptr);
                    custom_free(node);
                    return;
                }
            }
        }
        else // two children
        {
            BinarySearchTree<T>* parent = find_parent(node);
            BinarySearchTree<T>* floating_node = nullptr;
            if(parent->getLeft() == node)
            {
                parent->setLeft(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                custom_free(node);
            }
            else
            {
                parent->setRight(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                custom_free(node);
            }
        }
    }

    template <typename T>
    void BinarySearchTree<T>::remove(BinarySearchTree<T>* node, bool free)
    {
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to remove element (node NULL)");
            return;
        }
        if(node->getLeft() == nullptr && node->getRight() == nullptr) // no children
        {
            if(free)
                custom_free(node);
            return;
        }
        else if(node->getLeft() == nullptr || node->getRight() == nullptr) // only one child
        {
            BinarySearchTree<T>* parent = find_parent(node);
            if(node->getLeft() == nullptr)
            {
                if(parent->getLeft() == node)
                {
                    parent->setLeft(node->getRight());
                    node->setRight(nullptr);
                    if(free)
                        custom_free(node);
                    return;
                }
                else
                {
                    parent->setRight(node->getRight());
                    node->setRight(nullptr);
                    if(free)
                        custom_free(node);
                    return;
                }
            }
            else
            {
                if(parent->getRight() == node)
                {
                    parent->setRight(node->getLeft());
                    node->setLeft(nullptr);
                    if(free)
                        custom_free(node);
                    return;
                }
                else
                {
                    parent->setLeft(node->getLeft());
                    node->setRight(nullptr);
                    if(free)
                        custom_free(node);
                    return;
                }
            }
        }
        else // two children
        {
            BinarySearchTree<T>* parent = find_parent(node);
            BinarySearchTree<T>* floating_node = nullptr;
            if(parent->getLeft() == node)
            {
                parent->setLeft(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                if(free)
                    custom_free(node);
            }
            else
            {
                parent->setRight(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                if(free)
                    custom_free(node);
            }
        }
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
        if(!_is_init)
            return nullptr;
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
    BinarySearchTree<T>* BinarySearchTree<T>::find_parent(BinarySearchTree<T>* node)
    {
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to find parent of a node");
            return nullptr;
        }
        if(node->getData() > _data)
        {
            if(_right != nullptr)
            {
                if(_right == node)
                    return this;
                _right->find_parent(node);
            }
            else
                return nullptr;
        }
        else if(node->getData() < _data)
        {
            if(_left != nullptr)
            {
                if(_left == node)
                    return this;
                _left->find_parent(node);
            }
            else
                return nullptr;
        }
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
