#ifndef TASK_H
#define TASK_H

#include <string>

#include "LinkedList.h"

using namespace std;

/*
    Basic Task Structure
    Contains data for a single task only
*/
class Task {
private:
    string name;
    string notes;
    int dueDate; 

    LinkedList<string> tags;       
public:
    // Constructors
    Task() {
        this->name = "";
        this->notes = "";
        this->dueDate = 0;

        this->tags = LinkedList<string>();
    }

    Task(string name, int dueDate, string notes = "") : Task() {
        this->name = name;
        this->dueDate = dueDate;

        this->notes = notes;
    }

    // Getters/Setters
    void SetName(string newName) {
        this->name = newName;
    }
    string GetName() {
        return this->name;
    }

    void SetNotes(string newNotes) {
        this->notes = newNotes;
    }
    string GetNotes() {
        return this->notes;
    }

    void SetDueDate(int newDueDate) {
        // TODO verify dueDate
        if (true) {
            this->dueDate = newDueDate;
        }
    }
    int GetDueDate() {
        return this->dueDate;
    }

    LinkedList<string>* GetTags() {
        return &this->tags;
    }

    // Modifiers
    void AddTag(string newTag) {
        this->tags.Insert(newTag);
    }
    void RemoveTag(string tag) {
        this->tags.Delete(tag);
    }

    // Operator Overloads
    friend ostream& operator<<(ostream& os, const Task& t) {
        os << t.name;
    }

    friend bool operator==(const Task& t1, const Task& t2) {
        if (t1.name != t2.name) {
            return false;
        }
        if (t1.notes != t2.notes) {
            return false;
        }
        if (t1.dueDate != t2.dueDate) {
            return false;
        }
        return true;
    }

    friend bool operator!=(const Task& t1, const Task& t2) {
        return !(t1 == t2);
    }
};

#endif