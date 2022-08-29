#ifndef TASKTREE_H
#define TASKTREE_H

#include "TasksList.h"
#include "AVLTree.h"

/*
    AVLTree Type Structure of TaskList objects
    The dueDate is the key/comparison for balancing the tree
*/
class TaskTree : protected AVLTree<TasksList>{
public:
    TaskTree() : AVLTree() {}

    Task* Insert(Task task) {
        return this->Insert(task.GetDueDate(), task);
    }

    Task* Insert(int dueDate, Task task) {
        TasksList* ptr = this->Search(task.GetDueDate());
        if (ptr == nullptr) {
            ptr = AVLTree::Insert(TasksList(dueDate));
        }
        return ptr->value.Insert(task);
    }

    TasksList* Search(int dueDate) {
        return AVLTree::Search(TasksList(dueDate));
    }

    Task RemoveTask(Task* ptr) {
        if (ptr == nullptr) {
            return Task();
        }
        
        TasksList* listPtr = AVLTree::Search(TasksList(ptr->GetDueDate()));

        if (listPtr == nullptr) {
            return Task();
        }

        Task temp = *listPtr->value.Search(*ptr);
        listPtr->value.Delete(*ptr);

        if (listPtr->Empty()) {
            AVLTree::Delete(*listPtr);
        }

        return temp;
    }
    
};

#endif