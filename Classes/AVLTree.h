#ifndef AVLTREE_H
#define AVLTREE_H

#include "BSTree.h"

template <class K, class V = K>
class AVLTree : public BSTree<K, V> {
private:
    /*
        Parameters:
        currentNode - pointer to current iterrating node
        newNde - pointer to new node to insert
    */
    Node<K, V>* Insert(Node<K, V>* currentNode, Node<K, V>* newNode) {
        if (this->root == nullptr) {
            this->root = newNode;
            return this->root;
        }

        if (newNode->key < currentNode->key) {
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
            }
            else {
                currentNode->left = this->Insert(currentNode->left, newNode);
            }
        }
        else if (newNode->key > currentNode->key) {
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
            }
            else {
                currentNode->right = this->Insert(currentNode->right, newNode);
            }
        }
        else if (newNode->key == currentNode->key) {
            newNode = currentNode;
            return this->Balance(currentNode);
        }

        currentNode->height = this->CalculateHeight(currentNode);

        return this->Balance(currentNode);
    }

    Node<K, V>* Delete(Node<K, V>* node, K key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->key == key) {
            if (node->left != nullptr && node->right != nullptr) {
                Node<K, V>* successor = node->right;

                while (successor->left != nullptr) {
                    successor = successor->left;
                }

                node->key = successor->key;
                node->value = successor->value;

                node->right = this->Delete(node->right, successor->key);

                node->height = this->CalculateHeight(node);

                return this->Balance(node);
            }
            else if (node->left != nullptr) {
                Node<K, V>* temp = node->left;

                delete node;

                temp->height = this->CalculateHeight(node);
                return this->Balance(temp);
            }
            else if (node->right != nullptr) {
                Node<K, V>* temp = node->right;

                delete node;
                
                temp->height = this->CalculateHeight(node);
                return this->Balance(temp);
            }
            else {
                delete node;

                return nullptr;
            }
        }
        else if (key < node->key) {
            node->left = this->Delete(node->left, key);
        }
        else if (key > node->key) {
            node->right = this->Delete(node->right, key);
        }

        node->height = this->CalculateHeight(node);

        return node;
    }

    Node<K, V>* LeftRotate(Node<K, V>* node) {
        Node<K, V>* newRoot = node->right;
        Node<K, V>* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = this->CalculateHeight(node);
        newRoot->height = this->CalculateHeight(node);

        return newRoot;
    }

    Node<K, V>* RightRotate(Node<K, V>* node) {
        Node<K, V>* newRoot = node->left;
        Node<K, V>* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = this->CalculateHeight(node);
        newRoot->height = this->CalculateHeight(node);

        return newRoot;
    }

    int CalculateBalanceFactor(Node<K, V>* node) {
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

    Node<K, V>* Balance(Node<K, V>* node) {
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
    AVLTree() : BSTree<K, V>() {}

    V* Insert(K key, V value) {
        Node<K, V>* newNode = new Node<K, V>(key, value);
        
        this->root = this->Insert(this->root, newNode);
        
        return &newNode->value;
    }
    
    void Delete(K key) {
        this->root = this->Delete(this->root, key);
    }
};

#endif