#ifndef TASK_H
#define TASK_H

#include <string>

#include "LinkedList.h"

/*
    Basic Task Structure
    Contains data for a single task only
*/
class Task {
private:
    std::string name;
    std::string notes;
    int dueDate; 

    LinkedList<std::string> tags;       
public:
    // Constructors
    Task() {
        this->name = "";
        this->notes = "";
        this->dueDate = 0;

        this->tags = LinkedList<std::string>();
    }

    Task(std::string name, int dueDate, std::string notes = "") : Task() {
        this->name = name;
        this->dueDate = dueDate;

        this->notes = notes;
    }

    // Getters/Setters
    void SetName(std::string newName) {
        this->name = newName;
    }
    std::string GetName() {
        return this->name;
    }

    void SetNotes(std::string newNotes) {
        this->notes = newNotes;
    }
    std::string GetNotes() {
        return this->notes;
    }

    void SetDueDate(int newDueDate) {
        this->dueDate = newDueDate;
    }
    int GetDueDate() {
        return this->dueDate;
    }

    LinkedList<std::string>* GetTags() {
        return &this->tags;
    }

    // Modifiers
    void AddTag(std::string newTag) {
        this->tags.Insert(newTag);
    }
    void RemoveTag(std::string tag) {
        this->tags.Delete(tag);
    }

    // Operator Overloads
    friend std::ostream& operator<<(std::ostream& os, const Task& t) {
        os << t.name;
        
        return os;
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