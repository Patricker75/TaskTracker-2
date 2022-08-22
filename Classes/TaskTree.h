#ifndef TASKTREE_H
#define TASKTREE_H

#include "AVLTree.h"
#include "LinkedList.h"
#include "Task.h"

class TaskTree : protected AVLTree<int, LinkedList<Task>*> {
private:
    
public:
    TaskTree() {}
    
    Task* Insert(Task task) {
        return this->Insert(task.GetDueDate(), task);
    }

    Task* Insert(int dueDate, Task task) {
        LinkedList<Task>* taskList = this->Search(dueDate);
        if (taskList == nullptr) {
            taskList = new LinkedList<Task>();
            taskList = *AVLTree::Insert(dueDate, taskList);
        }

        return taskList->Insert(task);
    }

    LinkedList<Task>* Search(int dueDate) {
        LinkedList<Task>** ptr = AVLTree::Search(dueDate);
        if (ptr == nullptr) {
            return nullptr;
        }
        return *ptr;
    }

    Task* SearchTask(Task* taskPtr) {
        LinkedList<Task>* list = this->Search(taskPtr->GetDueDate());

        if (list == nullptr) {
            return nullptr;
        }

        return list->Search(*taskPtr);
    }

    void Remove(Task* taskPtr) {
        LinkedList<Task>* list = this->Search(taskPtr->GetDueDate());

        if (list == nullptr) {
            return;
        }

        list->Delete(*taskPtr);

        if (!list->Empty()) {
            return;
        }

        this->Delete(taskPtr->GetDueDate());
    }

    Node<int, LinkedList<Task>*>* GetRoot() {
        return this->root;
    }

};

#endif