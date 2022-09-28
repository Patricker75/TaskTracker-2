#ifndef TAGSHASHTABLE_H
#define TAGSHASHTABLE_H

#include "Chain.h"

class TagsHashTable {
private:
    LinkedList<Chain>* table;
    int size;

    int Hash(std::string tag) {
        int index = 0;
        for (int i = 0; i < 3; i++) {
            if (i > tag.length()) {
                break;
            }

            index += tag.at(i) * i;
        }

        return index % this->size;
    }
public:
    TagsHashTable() {
        this->size = 26;
        this->table = new LinkedList<Chain>[this->size]();
    }

    void Insert(std::string tag, Task* taskPtr) {
        int hashIndex = this->Hash(tag);

        Chain* chainPtr = this->table[hashIndex].Search(Chain(tag));
        if (chainPtr == nullptr) {
            chainPtr = this->table[hashIndex].Insert(Chain(tag));
        }        

        chainPtr->Insert(taskPtr);
    }

    Chain* Search(std::string tag) {
        int hashIndex = this->Hash(tag);

        return this->table[hashIndex].Search(tag);
    }
    
    void RemoveTask(std::string tag, Task* taskPtr) {
        if (taskPtr == nullptr) {
            return;
        }
        
        Chain* chainPtr = this->Search(tag);

        chainPtr->RemoveTask(taskPtr);
    }
};

#endif