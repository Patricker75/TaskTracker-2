#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
    T data;
    int height;
    
    Node<T>* next;
    Node<T>* prev;

    Node<T>* left;
    Node<T>* right;

    Node(T data) {
        this->data = data;

        this->height = 1;

        this->next = nullptr;
        this->prev = nullptr;
        this->left = nullptr;
        this->right = nullptr;

    }

    friend bool operator<(const Node<T>& n1, const Node<T>& n2) {
        return n1.data < n2.data;
    }
    friend bool operator>(const Node<T>& n1, const Node<T>& n2) {
        return n1.data > n2.data;
    }
    friend bool operator==(const Node<T>& n1, const Node<T>& n2) {
        return n1.data == n2.data;
    }
 };

#endif