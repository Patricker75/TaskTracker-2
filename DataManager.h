#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <ctime>

#include "IOController.h"
#include "Classes/TaskTree.h"
#include "Classes/TagsHashTable.h"

/*
    This class controls adding, removing, editing of all tasks stored
*/
class DataManager {
private:
    TaskTree taskTree;
    TagsHashTable tagHashTable;

    int currentDate;

    void PurgeTree(Node<TasksList>* node) {
        if (node == nullptr) {
            return;
        }

        // If node->data > currentDate, node->data is in the future
        // If node->data < currentDate, node->data is in the past
        if (currentDate < node->data) {
            PurgeTree(node->left);
        }
        else if (currentDate > node->data) {
            PurgeTree(node->left);

            this->DeleteTasksList(node->data.key);
        }
    }
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

        // Adding Task to HashTable
        Node<std::string>* tagNode = taskPtr->GetTags()->GetHead();
        while (tagNode != nullptr) {
            tagHashTable.Insert(tagNode->data, taskPtr);

            tagNode = tagNode->next;
        }
    }

    // Searches Tree for any Node matching the dueDate
    // Else returns nullptr
    TasksList* SearchTree(int dueDate) {
        return taskTree.Search(dueDate);
    }

    Chain* SearchHashTable(std::string tag) {
        return this->tagHashTable.Search(tag);
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

        Node<std::string>* tagNode = searchPtr->GetTags()->GetHead();
        while (tagNode != nullptr) {
            tagHashTable.RemoveTask(tagNode->data, searchPtr);

            tagNode = tagNode->next;
        }

        return taskTree.RemoveTask(searchPtr);
    }

    void RemoveTagFromTask(std::string tag, Task* ptr) {
        this->tagHashTable.RemoveTask(tag, ptr);
    }

    void DeleteTasksList(int dueDate) {
        // Search the tree for the TasksList
        TasksList* tasksList = this->SearchTree(dueDate);

        // Iterate through each node in the list and remove any Task*'s in the hashTable
        Node<Task>* taskNode = tasksList->GetList()->GetHead();
        while (taskNode != nullptr) {
            Node<std::string>* tagNode = taskNode->data.GetTags()->GetHead();

            while (tagNode != nullptr) {
                tagHashTable.RemoveTask(tagNode->data, &taskNode->data);

                tagNode = tagNode->next;
            }
            taskNode = taskNode->next;
        }

        this->taskTree.RemoveNode(dueDate);
    }

    void PurgeTree() {
        this->PurgeTree(this->GetRoot());
    }

    TagsHashTable* GetHashTable() {
        return &this->tagHashTable;
    }

    Node<TasksList>* GetRoot() {
        return taskTree.GetRoot();
    }

    void Save(std::string fileName) {
        SaveData(fileName, this->taskTree);
    }

    void Load(std::string fileName) {
        LoadData(fileName, this->taskTree, this->tagHashTable);
    }
};

#endif