#ifndef TAGSLIST_H
#define TAGSLIST_H

#include "Task.h"
#include "KeyValuePair.h"
#include "LinkedList.h"

/*
    key = dueDate
    value = List of Task*'s
*/
class TagsList : public KeyValuePair<int, LinkedList<Task*>> { 
public:
    TagsList() : KeyValuePair() {};

    TagsList(int dueDate) {
        this->key = dueDate;
        this->value = LinkedList<Task*>();
    }
    
    void Insert(Task* ptr) {
        if (ptr->GetDueDate() != this->key) {
            return;
        }

        this->value.Insert(ptr);
    }

    bool Empty() {
        return this->value.Empty();
    }
};

#endif