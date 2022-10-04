#ifndef AVLTREE_H
#define AVLTREE_H

#include "BSTree.h"

template <class T>
class AVLTree : public BSTree<T> {
private:
    /*
        Parameters:
        currentNode - pointer to current iterrating node
        newNde - pointer to new node to insert
    */
    Node<T>* Insert(Node<T>* currentNode, Node<T>* newNode) {
        if (this->root == nullptr) {
            this->root = newNode;
            return this->root;
        }

        if (newNode->data < currentNode->data) {
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
            }
            else {
                currentNode->left = this->Insert(currentNode->left, newNode);
            }
        }
        else if (newNode->data > currentNode->data) {
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
            }
            else {
                currentNode->right = this->Insert(currentNode->right, newNode);
            }
        }

        currentNode->height = this->CalculateHeight(currentNode);

        return this->Balance(currentNode);
    }

    Node<T>* Delete(Node<T>* node, T key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data == key) {
            if (node->left != nullptr && node->right != nullptr) {
                Node<T>* successor = node->right;

                while (successor->left != nullptr) {
                    successor = successor->left;
                }

                node->data = successor->data;

                node->right = this->Delete(node->right, successor->data);

                node->height = this->CalculateHeight(node);

                return this->Balance(node);
            }
            else if (node->left != nullptr) {
                Node<T>* temp = node->left;

                delete node;

                temp->height = this->CalculateHeight(temp);
                return this->Balance(temp);
            }
            else if (node->right != nullptr) {
                Node<T>* temp = node->right;

                delete node;
                
                temp->height = this->CalculateHeight(temp);
                return this->Balance(temp);
            }
            else {
                delete node;

                return nullptr;
            }
        }
        else if (key < node->data) {
            node->left = this->Delete(node->left, key);
        }
        else if (key > node->data) {
            node->right = this->Delete(node->right, key);
        }

        node->height = this->CalculateHeight(node);

        return this->Balance(node);
    }

    Node<T>* LeftRotate(Node<T>* node) {
        Node<T>* newRoot = node->right;
        Node<T>* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = this->CalculateHeight(node);
        newRoot->height = this->CalculateHeight(node);

        return newRoot;
    }

    Node<T>* RightRotate(Node<T>* node) {
        Node<T>* newRoot = node->left;
        Node<T>* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = this->CalculateHeight(node);
        newRoot->height = this->CalculateHeight(node);

        return newRoot;
    }

    int CalculateBalanceFactor(Node<T>* node) {
        int leftHeight = 0;
        int rightHeight = 0;

        if (node->left != nullptr) {
            leftHeight = node->left->height;
        }
        if (node->right != nullptr) {
            rightHeight = node->right->height;
        }

        return leftHeight - rightHeight;
    }

    Node<T>* Balance(Node<T>* node) {
        int balanceFactor = this->CalculateBalanceFactor(node);

        /*
        Balance Factor Cases:
        >+1 - Left Heavy
        <-1 - Right Heavy
        */

        if (balanceFactor > 1) {
            if (node->left != nullptr) {
                int leftBalanceFactor = this->CalculateBalanceFactor(node->left);

                if (leftBalanceFactor < 0) {
                    node->left = this->LeftRotate(node->left);

                    node->left->height = this->CalculateHeight(node->left);
                }
            }

            node = this->RightRotate(node);
        }
        else if (balanceFactor < -1) {
            if (node->right != nullptr) {
                int rightBalanceFactor = this->CalculateBalanceFactor(node->right);

                if (rightBalanceFactor > 0) {
                    node->right = this->RightRotate(node->right);

                    node->right->height = this->CalculateHeight(node->right);
                }
            }

            node = this->LeftRotate(node);            
        }

        node->height = this->CalculateHeight(node);

        return node;
    }
public:
    AVLTree() : BSTree<T>() {};
    
    T* Insert(T data) {
        Node<T>* newNode = new Node<T>(data);

        this->root = this->Insert(this->root, newNode);

        return &newNode->data;
    }

    void Delete(T key) {
        this->root = this->Delete(this->root, key);
    }
};

#endif