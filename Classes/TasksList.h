#ifndef TASKSLIST_H
#define TASKSLIST_H

#include "Task.h"
#include "KeyValuePair.h"


/*
    LinkedList of Task objects
    All Task's in the list have the same dueDate

    key = dueDate
    value = LinkedList
*/
class TasksList : public KeyValuePair<int, LinkedList<Task>> {
public:
    TasksList() : KeyValuePair() {}

    TasksList(int dueDate) {
        this->key = dueDate;
    };

    Task* Insert(Task task) {
        // Checking that task's dueDate == this object's dueDate
        // Otherwise, return nullptr
        if (this->key != task.GetDueDate()) {
            return nullptr;
        }

        return value.Insert(task);
    }

    LinkedList<Task>* GetList() {
        return &this->value;
    }

    bool Empty() {
        return value.Empty();
    }
};


#endif