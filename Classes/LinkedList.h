#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

    int size;
public:
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;

        this->size = 0;
    };

    T* Insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        this->size++;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;

            return &newNode->data;
        }

        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;

        return &newNode->data;
    }

    T* Search(T key) {
        Node<T>* node = this->head;

        while (node != nullptr && node->data != key) {
            node = node->next;
        }

        if (node == nullptr) {
            return nullptr;
        }
        return &node->data;
    }

    void Delete(T key) {
        Node<T>* current = this->head;

        // Current will be node to delete OR nullptr
        while(current != nullptr && current->data != key) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        // Only Lists of 1 Element
        if (current == this->head && current == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        }
        // Current Node is the Head Node
        else if (current == this->head) {
            this->head = current->next;
            this->head->prev = nullptr;
        }
        // Current Node is the Tail Node
        else if (current == this->tail) {
            this->tail = current->prev;
            this->tail->next = nullptr;
        }
        // Current Node is just a Node
        else {
            // Connecting the Predeccessor to Successor of Current Node
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        this->size--;

        delete current;
    }

    bool Empty() {
        return this->head == nullptr;
    }

    Node<T>* GetHead() {
        return this->head;
    }
    
    Node<T>* GetTail() {
        return this->tail;
    }

    int GetSize() {
        return this->size;
    }
};

#endif