#ifndef NODE_H
#define NODE_H

template <class K, class V = K>
struct Node {
private: 
    Node() {
        this->height = 1;

        this->next = nullptr;
        this->prev = nullptr;
        
        this->left = nullptr;
        this->right = nullptr;
    }
public:
    Node(K key) : Node() {
        this->key = key;
    }

    Node(K key, V value) : Node() {
        this->key = key;
        this->value = value;
    }

    K key;
    V value;

    int height;

    Node<K, V>* next;
    Node<K, V>* prev;

    Node<K, V>* left;
    Node<K, V>* right;
};

#endif