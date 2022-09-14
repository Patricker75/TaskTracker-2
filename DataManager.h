#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Classes/TaskTree.h"

/*
    This class controls adding, removing, editing of all tasks stored
*/
class DataManager {
private:
    TaskTree taskTree;
public:
    DataManager() {}

    // Adds a Task object to the tree
    void AddTask(Task newTask) {
        // Checking for duplicate tasks
        TasksList* tasksList = taskTree.Search(newTask.GetDueDate());
        
        if (tasksList != nullptr) {
            LinkedList<Task>* list = tasksList->GetList();
            if (list->Search(newTask) != nullptr) {
                return;
            }
        }

        // Add New Unique Task
        Task* taskPtr = taskTree.Insert(newTask.GetDueDate(), newTask);        
    }

    // Searches Tree for any Node matching the dueDate
    // Else returns nullptr
    TasksList* SearchTree(int dueDate) {
        return taskTree.Search(dueDate);
    }

    // Returns a Task object, and removes it from the tree entirely
    Task RemoveTask(Task* ptr) {
        TasksList* tasksList = this->SearchTree(ptr->GetDueDate());

        if (tasksList == nullptr) {
            return Task();
        }

        LinkedList<Task>* list = tasksList->GetList();
        Task* searchPtr = list->Search(*ptr);

        if (searchPtr == nullptr) {
            return Task();
        }

        Task deletedTask = *searchPtr;
        list->Delete(deletedTask);
        return deletedTask;
    }

    Node<TasksList>* GetRoot() {
        return taskTree.GetRoot();
    }
};

#endif