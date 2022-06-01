// This file is a part of Akel
// Authors : @kbz_8
// Created : 17/11/2021
// Updated : 01/06/2022

#include <Utils/Containers/bst.h>

namespace Ak
{
    void Error(std::string message, ...);
    void Warning(std::string message, ...);

    template <typename T, typename ... Args>
    T* memAlloc(Args&& ... args);
    template <typename T>
    void memFree(T* ptr);

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(T&& data) : _data(std::forward<T>(data)), is_init(true) {}

    template <typename T>
    void BinarySearchTree<T>::add(T&& data)
    {
        if(_greater(std::forward<T>(data), _data))
        {
            if(_right != nullptr)
                _right->add(std::forward<T>(data));
            else
                _right = memAlloc<BinarySearchTree<T>>(std::forward<T>(data));
        }
        else
        {
            if(_left != nullptr)
                _left->add(std::forward<T>(data));
            else
                _left = memAlloc<BinarySearchTree<T>>(std::forward<T>(data));
        }
        is_init = true;
    }

    template <typename T>
    void BinarySearchTree<T>::add(BinarySearchTree<T>* node)
    {
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to add node (NULL node)");
            return;
        }
        if(node == this)
        {
            Warning("Binary Search Tree : unable to add a node (trying to add a node to itself)");
            return;
        }
        if(_greater(node->getData(), _data))
        {
            if(_right != nullptr)
                _right->add(node);
            else
                _right = node;
        }
        else
        {
            std::cout << node << std::endl;
            if(_left != nullptr)
                _left->add(node);
            else
                _left = node;
        }
        is_init = true;
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
            memFree(node);
            return;
        }
        else if(node->getLeft() == nullptr || node->getRight() == nullptr) // only one child
        {
            BinarySearchTree<T>* parent = find_parent(node);
            if(parent == nullptr) // root node
            {
                // add the left subtree to the right one
                if(node->getRight() != nullptr)
                    node->getRight()->add(_left);
                else
                    node->setRight(node->getLeft());
                node->setLeft(nullptr);
                
                // right subtree becomes the new root
                if(node->getRight() != nullptr)
                {
                    parent = node->getRight(); // recycling the pointer for the environment
                    node->setData(std::move(parent->getData()));
                    node->setRight(parent->getRight());
                    node->setLeft(parent->getLeft());
                }
                return;
            }
            else if(node->getLeft() == nullptr)
            {
                if(parent->getLeft() == node)
                {
                    parent->setLeft(node->getRight());
                    node->setRight(nullptr);
                    memFree(node);
                    return;
                }
                else
                {
                    parent->setRight(node->getRight());
                    node->setRight(nullptr);
                    memFree(node);
                    return;
                }
            }
            else
            {
                if(parent->getRight() == node)
                {
                    parent->setRight(node->getLeft());
                    node->setLeft(nullptr);
                    memFree(node);
                    return;
                }
                else
                {
                    parent->setLeft(node->getLeft());
                    node->setRight(nullptr);
                    memFree(node);
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
                memFree(node);
            }
            else
            {
                parent->setRight(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                memFree(node);
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
                memFree(node);
            return;
        }
        else if(node->getLeft() == nullptr || node->getRight() == nullptr) // only one child
        {
            BinarySearchTree<T>* parent = find_parent(node);
            if(parent == nullptr) // root node
            {
                // add the left subtree to the right one
                if(node->getRight() != nullptr)
                    node->getRight()->add(_left);
                else
                    node->setRight(node->getLeft());
                node->setLeft(nullptr);
                
                // right subtree becomes the new root
                if(node->getRight() != nullptr)
                {
                    parent = node->getRight(); // recycling the pointer for the environment
                    node->setData(std::move(parent->getData()));
                    node->setRight(parent->getRight());
                    node->setLeft(parent->getLeft());
                }
                return;
            }
            else if(node->getLeft() == nullptr)
            {
                if(parent->getLeft() == node)
                {
                    parent->setLeft(node->getRight());
                    node->setRight(nullptr);
                    if(free)
                        memFree(node);
                    return;
                }
                else
                {
                    parent->setRight(node->getRight());
                    node->setRight(nullptr);
                    if(free)
                        memFree(node);
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
                        memFree(node);
                    return;
                }
                else
                {
                    parent->setLeft(node->getLeft());
                    node->setRight(nullptr);
                    if(free)
                        memFree(node);
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
                    memFree(node);
            }
            else
            {
                parent->setRight(node->getRight());
                floating_node = node->getRight();
                while(floating_node->getLeft() != nullptr)
                    floating_node = floating_node->getLeft();
                floating_node->setLeft(node->getLeft());
                if(free)
                    memFree(node);
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
        if(!is_init)
        {
            Error("Binary Search Tree : unable to find an uninit node");
            return nullptr;
        }
        if(_greater(std::forward<T>(data), _data))
        {
            if(_right != nullptr)
                return _right->find(std::forward<T>(data));
            Error("Binary Search Tree : unable to find a node");
            return nullptr;
        }
        else if(_less(std::forward<T>(data), _data))
        {
            if(_left != nullptr)
                return _left->find(std::forward<T>(data));
            Error("Binary Search Tree : unable to find a node");
            return nullptr;
        }
        else
            return this;
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::find_parent(T&& data)
    {
        if(_greater(std::forward<T>(data), _data))
        {
            if(_right != nullptr)
            {
                if(_equal(_right->getData(), data))
                    return this;
                return _right->find_parent(std::forward<T>(data));
            }
            Error("Binary Search Tree : unable to find the parent of a node");
            return nullptr;
        }
        else if(_less(std::forward<T>(data), _data))
        {
            if(_left != nullptr)
            {
                if(_equal(_left->getData(), data))
                    return this;
                return _left->find_parent(std::forward<T>(data));
            }
            Error("Binary Search Tree : unable to find the parent of a node");
            return nullptr;
        }
        return nullptr;
    }

    template <typename T>
    BinarySearchTree<T>* BinarySearchTree<T>::find_parent(BinarySearchTree<T>* node)
    {
        if(node == nullptr)
        {
            Error("Binary Search Tree : unable to find the parent of a null node");
            return nullptr;
        }
        if(_greater(node->getData(), _data))
        {
            if(_right != nullptr)
            {
                if(_right == node)
                    return this;
                return _right->find_parent(node);
            }
            Error("Binary Search Tree : unable to find the parent of a node");
            return nullptr;
        }
        else if(_less(node->getData(), _data))
        {
            if(_left != nullptr)
            {
                if(_left == node)
                    return this;
                return _left->find_parent(node);
            }
            Error("Binary Search Tree : unable to find the parent of a node");
            return nullptr;
        }
        return nullptr;
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        // will free all subtrees by recursion
        if(_left != nullptr)
            memFree(_left);
        if(_right != nullptr)
            memFree(_right);
    }
}
