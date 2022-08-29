#ifndef BSTREE_H
#define BSTREE_H

#include "Node.h"

template <class T>
class BSTree {
protected:
    Node<T>* root;

    Node<T>* Insert(Node<T>* currentNode, Node<T>* newNode) {
        if (currentNode == nullptr) {
            return newNode;
        }

        if (newNode->data < currentNode->data) {
            currentNode->left = this->Insert(currentNode->left, newNode);
        }
        else if (newNode->data > currentNode->data) {
            currentNode->right = this->Insert(currentNode->right, newNode);
        }

        currentNode->height = this->CalculateHeight(currentNode);
        
        return currentNode;
    }

    T* Search(Node<T>* currentNode, T key) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        
        if (key == currentNode->data) {
            return &currentNode->data;
        }

        if (key < currentNode->data) {
            return this->Search(currentNode->left, key);
        }
        else if (key > currentNode->data) {
            return this->Search(currentNode->right, key);
        }
    }

    Node<T>* Delete(Node<T>* currentNode, T key) {
        if (currentNode == nullptr) {
            return nullptr;
        }

        if (currentNode->data != key) {
            if (key < currentNode->data) {
                currentNode->left = this->Delete(currentNode->left, key);
            }
            else if (key > currentNode->data) {
                currentNode->right = this->Delete(currentNode->right, key);
            }

            return currentNode;
        }

        if (currentNode->left != nullptr && currentNode->right != nullptr) {
            Node<T>* successor = currentNode->right;

            while (successor->left != nullptr) {
                successor = successor->left;
            }

            currentNode->data = successor->data;

            currentNode->right = this->Delete(currentNode->right, successor->data);

            return currentNode;
        }
        else if (currentNode->left != nullptr) {
            Node<T>* temp = currentNode->left;

            delete currentNode;
            return temp;
        }
        else if (currentNode->right != nullptr) {
            Node<T>* temp = currentNode->right;

            delete currentNode;
            return temp;
        }
        else {
            delete currentNode;
            return nullptr;
        }
    }

    int CalculateHeight(Node<T>* node) {
        int leftHeight = 0;
        int rightHeight = 0;

        if (node->left != nullptr) {
            leftHeight = node->left->height;
        }
        if (node->right != nullptr) {
            rightHeight = node->right->height;
        }

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }
        return rightHeight + 1;
    }
public:
    BSTree() {
        this->root = nullptr;
    };

    T* Insert(T data) {
        Node<T>* newNode = new Node<T>(data);

        this->root = this->Insert(this->root, newNode);

        return &newNode->data;
    }

    T* Search(T key) {
        return this->Search(this->root, key);
    }

    void Delete(T key) {
        this->root = this->Delete(this->root, key);
    }

    Node<T>* GetRoot() {
        return this->root;
    }
    
};

#endif