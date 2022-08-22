#ifndef TAGHASHTABLE_H
#define TAGHASHTABLE_H

#include <string>

#include "LinkedList.h"
#include "Task.h"

using namespace std;

/*
    Hash Table:
    - Consists of buckets
    - Collision Handling with Chaining
    
    - Bucket:
        - LinkedList of Chains
        - Each Chain:
            Contains a string Tag as the key
            Contains a LinkedList of Task*
*/

class Chain {
private:
    string tag;
    LinkedList<Task*>* ptrList;
public:
    Chain() {}

    Chain(string tag) {
        this->tag = tag;
        this->ptrList = new LinkedList<Task*>();
    }

    void AddTask(Task* task) {
        Task** ptr = this->ptrList->Search(task);
        
        if (ptr == nullptr) {
            this->ptrList->Insert(task);
        }
    }

    void RemoveTask() {
        
    }

    LinkedList<Task*>* GetList() {
        return this->ptrList;
    }

    friend bool operator==(const Chain& c1, const Chain& c2) {
        if (c1.tag == c2.tag) {
            return true;
        }
        return false;
    }

    friend bool operator!=(const Chain& c1, const Chain& c2) {
        return !(c1 == c2);
    }
};

struct Bucket {
    Bucket() {
        this->collisions = new LinkedList<Chain>();
    }
    LinkedList<Chain>* collisions;
};

class TagHashTable {
private:
    int size;
    Bucket** table;
    
    int Hash(string tag) {
        int total = 0;
        for (int i = 0; i < tag.length() && i < 2; i++) {
            total += tag.at(i) * (i + 1);
        }

        return total % this->size;
    }
public:
    TagHashTable(int size=11) {
        this->size = size;
        this->table = new Bucket*[size]();
    }

    void Insert(string tag, Task* taskPtr) {
        int hashIndex = this->Hash(tag);

        if (this->table[hashIndex] == nullptr) {
            this->table[hashIndex] = new Bucket();
            // ?
        }
        Bucket* targetBucket = this->table[hashIndex];

        Chain* ptr = targetBucket->collisions->Search(tag);
        
        // Creates a new Chain if the tag is NOT found
        if (ptr == nullptr) {
            ptr = targetBucket->collisions->Insert(Chain(tag));
        }

        ptr->AddTask(taskPtr);
    }

    LinkedList<Task*>* Search(string tag) {
        int hashIndex = this->Hash(tag);

        Bucket* targetBucket = this->table[hashIndex];

        if (targetBucket == nullptr) {
            return nullptr;
        }

        Chain* targetChain = targetBucket->collisions->Search(tag);

        if (targetChain == nullptr) {
            return nullptr;
        }

        return targetChain->GetList();
    }
    
    Bucket** GetTable() {
        return this->table;
    }

    int GetSize() {
        return this->size;
    }
};

#endif