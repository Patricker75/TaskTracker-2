#ifndef BSTREE_H
#define BSTREE_H

#include "Node.h"

template <class K, class V = K>
class BSTree {
protected:
    Node<K, V>* root;

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
        else {
            newNode = currentNode;
            return currentNode;
        }

        currentNode->height = this->CalculateHeight(currentNode);

        return currentNode;
    }

    V* Search(Node<K, V>* node, K key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->key == key) {
            return &node->value;
        }
        else if (key < node->key) {
            return this->Search(node->left, key);
        }
        else if (key > node->key) {
            return this->Search(node->right, key);
        }
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

                return node;
            }
            else if (node->left != nullptr) {
                Node<K, V>* temp = node->left;

                delete node;
                return temp;
            }
            else if (node->right != nullptr) {
                Node<K, V>* temp = node->right;

                delete node;
                return temp;
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

    int CalculateHeight(Node<K, V>* node) {
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
    
    V* Insert(K key, V value=V()) {
        Node<K, V>* newNode = new Node<K, V>(key, value);
        // V* ptr = nullptr;

        this->root = this->Insert(this->root, newNode);

        return &newNode->value;
    }

    V* Search(K key) {
        return this->Search(this->root, key);
    }

    void Delete(K key) {
        this->root = this->Delete(this->root, key);
    }

    Node<K, V>* GetRoot() {
        return this->root;
    }
};

#endif