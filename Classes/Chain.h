#ifndef CHAIN_H
#define CHAIN_H

#include "TagTree.h"

/*
    key = tag
    value = tagTree
*/
class Chain : public KeyValuePair<std::string, TagTree> {
public:
    Chain() : KeyValuePair() {}
    
    Chain(std::string tag) {
        this->key = tag;
        this->value = TagTree();
    }

    void Insert(Task* ptr) {
        if (ptr->GetTags()->Search(this->key) == nullptr) {
            return;
        }

        this->value.Insert(ptr);
    }

    void RemoveTask(Task* ptr) {
        this->value.RemoveTask(ptr);
    }

    bool Empty() {
        return this->value.Empty();
    }
};

#endif