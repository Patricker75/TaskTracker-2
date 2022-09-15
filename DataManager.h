#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <ctime>

#include "IOController.h"
#include "Classes/TaskTree.h"

/*
    This class controls adding, removing, editing of all tasks stored
*/
class DataManager {
private:
    TaskTree taskTree;
    int currentDate;
public:
    DataManager() {
        time_t temp = std::time(0);
        tm* now = std::gmtime(&temp); 

        this->currentDate = (now->tm_year + 1900) * 10000 + now->tm_mon * 100 + now->tm_mday;
    }

    // Adds a Task object to the tree
    void AddTask(Task newTask) {
        // Checking if task has valid dueDate (i.e. not in the past)
        if (newTask.GetDueDate() < currentDate) {
            return;
        }

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

        return taskTree.RemoveTask(searchPtr);
    }

    void DeleteTasksList(int dueDate) {
        this->taskTree.RemoveNode(dueDate);
    }

    Node<TasksList>* GetRoot() {
        return taskTree.GetRoot();
    }

    void Save(std::string fileName) {
        SaveData(fileName, this->taskTree);
    }

    void Load(std::string fileName) {
        this->taskTree = LoadData(fileName);
    }
};

#endif