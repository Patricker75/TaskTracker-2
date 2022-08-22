#ifndef PROGRAMMANAGER_H
#define PROGRAMMANAGER_H

#include <string>

#include "TaskTree.h"
#include "TagHashTable.h"

using namespace std;

class DataManager {
private:
    TaskTree tasks;
    TagHashTable tagTable;
public:
    DataManager() {
        tasks = TaskTree();
        tagTable = TagHashTable();
    };

    Task* AddTask(string name, int dueDate, string notes="", LinkedList<string>* tags=nullptr) {
        Task newTask = Task(name, dueDate, notes);

        Task* taskPtr = tasks.Insert(newTask);

        if (tags != nullptr) {
            Node<string>* node = tags->GetHead();

            while (node != nullptr) {
                taskPtr->AddTag(node->key);
                tagTable.Insert(node->key, taskPtr);

                node = node->next;
            }            
        }

        return taskPtr;
    }

    Task* AddTask(Task task) {
        Task* taskPtr = tasks.SearchTask(&task);

        if (taskPtr != nullptr) {
            return taskPtr;
        }

        taskPtr = tasks.Insert(task);

        Node<string>* node = taskPtr->GetTags()->GetHead();
        while (node != nullptr) {
            tagTable.Insert(node->key, taskPtr);

            node = node->next;
        }

        return taskPtr;
    }
    
    void RemoveTask(Task* taskPtr) {
        tasks.Remove(taskPtr);
    }

    LinkedList<Task>* SearchDate(int date) {
        return tasks.Search(date);
    }

    LinkedList<Task*>* SearchTag(string tag) {
        return tagTable.Search(tag);
    }

    Node<int, LinkedList<Task>*>* GetRoot() {
        return this->tasks.GetRoot();
    }
};

#endif