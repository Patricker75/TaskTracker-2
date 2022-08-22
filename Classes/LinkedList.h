#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <class K, class V = K>
class LinkedList {
private:
    Node<K, V>* head;
    Node<K, V>* tail;

    int size;
public:
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;

        this->size = 0;
    };

    V* Insert(K key) {
        return this->Insert(key, key);
    }

    V* Insert(K key, V value) {
        Node<K, V>* newNode = new Node<K, V>(key, value);
        this->size++;

        if (this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;

            return &newNode->value;
        }

        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;

        return &newNode->value;
    }

    V* Search(K key) {
        Node<K, V>* node = this->head;

        while (node != nullptr && node->key != key) {
            node = node->next;
        }

        if (node == nullptr) {
            return nullptr;
        }
        return &node->value;
    }

    void Delete(K key) {
        Node<K, V>* current = this->head;

        // Current will be node to delete OR nullptr
        while(current != nullptr && current->key != key) {
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

    Node<K, V>* GetHead() {
        return this->head;
    }
    
    Node<K, V>* GetTail() {
        return this->tail;
    }

    int GetSize() {
        return this->size;
    }
};

#endif