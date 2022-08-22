#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <class T>
class Queue {
private:
    Node<T>* front;
    Node<T>* back;
public:
    Queue() {
        this->front = nullptr;
        this->back = nullptr;
    };

    void Enqueue(T data) {
        Node<T>* node = new Node<T>(data);
        
        if (this->front == nullptr) {
            this->front = node;
            this->back = this->front;

            return;
        }

        this->back->next = node;
        this->back = node;
    }

    T Dequeue() {
        if (this->front == nullptr) {
            return 0;
        }

        Node<T>* node = this->front;
        this->front = node->next;
        return node->key;
    }
    
    bool IsEmpty() {
        return this->front == nullptr;
    }
};

#endif