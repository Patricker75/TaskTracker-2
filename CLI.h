#ifndef CLI_H
#define CLI_H

#include <iostream>

#include "DataManager.h"

DataManager dm;

enum class InputType {name, notes, dueDate, add_tags, remove_tags};

std::string FormatDueDate(int dueDate) {
    int day = dueDate % 100;
    dueDate /= 100;

    int month = dueDate % 100;
    dueDate /= 100;

    int year = dueDate;

    return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
}

template <class T>
void PrintLinkedList(Node<T>* node) {
    while (node != nullptr) {
        std::cout << "\t" << node->data << std::endl;

        node = node->next;
    }
}

template <class T>
void PrintLinkedList(Node<T*>* node) {
    while (node != nullptr) {
        std::cout << "\t" << *node->data << std::endl;

        node = node->next;
    }
}

void PrintTaskTree(Node<TasksList>* node) {
    if (node == nullptr) {
        return;
    }

    PrintTaskTree(node->left);


    // Prints out InOrderPrint
    std::cout << FormatDueDate(node->data.key) << std::endl;

    LinkedList<Task>* list = node->data.GetList();
    PrintLinkedList(list->GetHead());
    std::cout << std::endl;


    PrintTaskTree(node->right);
}

void PrintTagTree(Node<TagsList>* node) {
    if (node == nullptr) {
        return;
    }

    PrintTagTree(node->left);


    // Prints out InOrderPrint
    std::cout << FormatDueDate(node->data.key) << std::endl;

    LinkedList<Task*>* list = node->data.GetList();
    PrintLinkedList(list->GetHead());
    std::cout << std::endl;


    PrintTagTree(node->right);
}

void PrintTaskArray(Task** array, int size) {
    if (array == nullptr) {
        return;
    }
    for (int i = 0; i < size; i++) {
        std::cout << i << " - " <<  *array[i] << std::endl;
    }
}

void PrintTask(Task* ptr) {
    std::cout << "Task Name: " << ptr->GetName() << std::endl;
    std::cout << "Due Date: " << FormatDueDate(ptr->GetDueDate()) << std::endl;
    std::cout << "Notes: " << ptr->GetNotes() << std::endl;
    std::cout << "Tags: " << std::endl;
    PrintLinkedList(ptr->GetTags()->GetHead());
}

bool IsValidDate(int day, int month, int year) {
    /*
    Checks if:
        month is in range (1-12)
        day is range (1-31)
            then checks for (1-28) on year(s) % 4 != 0 and month == 2
                OR checks (1-29) on year(s) % 4 == 0 and month == 2
            then checks for month == (4,6,9,11) for day in range (1-30) 
    */
    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 2) {
        if (day > 28 && year % 4 != 0) {
            return false;
        }
        else if (day > 29) {
            return false;
        }
    }

    if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
        return false;
    }

    return true;
} 

void InputHandler(InputType type, void* ptr) {
    std::string input = "";
    switch (type) {
        case InputType::name: {
            std::string* namePtr = (std::string*) ptr;

            std::cout << "Name of Task: ";
            while (input.empty()) {
                std::getline(std::cin, input);
            }

            *namePtr = input;
            break;
        }

        case InputType::notes: {
            std::string* notesPtr = (std::string*) ptr;
            
            std::cout << "Task's Notes: ";
            std::getline(std::cin, input);

            *notesPtr = input;
            break;
        }
            
        case InputType::dueDate: {
            int* dueDatePtr = (int*) ptr;

            std::cout << "Date of Task:" << std::endl;
            int month, day, year;

            std::cout << "Month: ";
            while (input.empty()) {
                std::getline(std::cin, input);
            }
            month = std::stoi(input);
            input = "";

            std::cout << "Day: ";
            while (input.empty()) {
                std::getline(std::cin, input);
            }
            day = std::stoi(input);
            input = "";

            std::cout << "Year: ";
            while (input.empty()) {
                std::getline(std::cin, input);
            }
            year = std::stoi(input);

            if (IsValidDate(day, month, year)) {
                *dueDatePtr = year * 10000 + month * 100 + day;
            }
            else {
                std::cout << "Invalid Date" << std::endl;
                InputHandler(InputType::dueDate, dueDatePtr);
            }
            break;
        }

        case InputType::add_tags: {
            Task* taskPtr = (Task*) ptr;

            std::cout << "Adding Tags: (leave blank to stop)" << std::endl;
            do {
                std::getline(std::cin, input);
                
                if (!input.empty()) {
                    taskPtr->AddTag(input);
                }
            } while (!input.empty());
            break;
        }

        case InputType::remove_tags: {
            Task* taskPtr = (Task*) ptr;

            std::cout << "Tags of Task" << std::endl;
            PrintLinkedList(taskPtr->GetTags()->GetHead());

            std::cout << "Removing Tags: (leave blank to stop)" << std::endl;
            do {
                std::getline(std::cin, input);
                
                taskPtr->RemoveTag(input);
                dm.RemoveTagFromTask(input, taskPtr);
            } while (!input.empty());
            break;
        }
    }
}

// Takes in int&, Returns Array of Tasks
Task** SearchTasksList(int& size) {
    int searchDate;
    InputHandler(InputType::dueDate, &searchDate);

    TasksList* tasks = dm.SearchTree(searchDate);
    if (tasks == nullptr) {
        std::cout << "No Task with Date: " << FormatDueDate(searchDate);
        size = 0;
        return nullptr;
    }

    Task** taskArray = tasks->ListToArray();
    size = tasks->GetList()->GetSize();

    std::cin.clear();

    return taskArray;
}

Task* SearchForTask() {
    int size;
    Task** array = SearchTasksList(size);
    if (array == nullptr) {
        return nullptr;
    }

    int index;

    PrintTaskArray(array, size);
    std::cout << "Which index to Print: ";
    std::cin >> index;

    std::cout << std::endl;

    return array[index];
}

// Function allows user to edit various properties of the task
void EditTask(Task* ptr) {
    PrintTask(ptr);

    int choice = 0;
    while (choice >= 0) {    
        std::cout << "0 - Name" << std::endl;
        std::cout << "1 - Due Date" << std::endl;
        std::cout << "2 - Notes" << std::endl;
        std::cout << "3 - Add Tags" << std::endl;
        std::cout << "4 - Remove Tags" << std::endl;
        std::cout << "-1 - Exit" << std::endl;

        std::string line;
        while (line.empty()) {
            std::getline(std::cin, line);
        }

        choice = std::stoi(line);

        // Change Name
        if (choice == 0) {
            InputHandler(InputType::name, &line);
            ptr->SetName(line);
        }
        // Change DueDate
        else if (choice == 1) {
            int newDueDate = -1;
            InputHandler(InputType::dueDate, &newDueDate);
            ptr->SetDueDate(newDueDate);
        }
        // Change Notes
        else if (choice == 2) {
            InputHandler(InputType::notes, &line);
            ptr->SetNotes(line);
        }
        // Add Tag(s)
        else if (choice == 3) {
            InputHandler(InputType::add_tags, ptr);
        }
        // Remove Tag(s)
        else if (choice == 4) {
            InputHandler(InputType::remove_tags, ptr);
        }
        // Exit
        else {
            choice == -1;
        }
    }
}

void PrintMenu() {
    std::cout << "0 - Print Tree" << std::endl;
    std::cout << "1 - Add Task" << std::endl;
    std::cout << "2 - Remove Task" << std::endl;
    std::cout << "3 - Edit Task" << std::endl;
    std::cout << "4 - Print Task" << std::endl;
    std::cout << "5 - Remove Entire Date" << std::endl;
    std::cout << "6 - Print All Tags" << std::endl;
    std::cout << "7 - Search Task by Tag" << std::endl;
    std::cout << "8 - Delete All Old Tasks" << std::endl;
    std::cout << "-1 - Exit" << std::endl;
}

// Function takes user input and creates a new task
void AddTask() {
    std::string name = "";
    int dueDate = -1;
    std::string notes = "";

    InputHandler(InputType::name, &name);
    std::cout << std::endl;
    InputHandler(InputType::dueDate, &dueDate);
    std::cout << std::endl;
    InputHandler(InputType::notes, &notes);

    Task newTask(name, dueDate, notes);
    
    std::cout << std::endl;
    InputHandler(InputType::add_tags, &newTask);

    dm.AddTask(newTask);
}

// Function searches for a task then removes it from the tree
void RemoveTask() {
    Task* toRemove = SearchForTask();
    
    if (toRemove == nullptr) {
        return;
    }

    dm.RemoveTask(toRemove);
}

// Function searches for a task then calls EditTask()
void UpdateTask() {
    Task* editting = SearchForTask();
    
    if (editting == nullptr) {
        return;
    }
    
    int oldDueDate = editting->GetDueDate();
    EditTask(editting);
    if (oldDueDate == editting->GetDueDate()) {
        return;
    }

    // Must Update Tree to Reflect Task's New DueDate
    dm.AddTask(*editting);
    TasksList* list = dm.SearchTree(oldDueDate);
    list->GetList()->Delete(*editting);
}

void RemoveWholeDate() {
    int deleteDate;
    InputHandler(InputType::dueDate, &deleteDate);

    dm.DeleteTasksList(deleteDate);
}

void PrintAllTags() {
    TagsHashTable* table = dm.GetHashTable();
    int size = table->GetSize();

    // TODO Implement LinkedList Sorting

    std::cout << "Stored Tags: " << std::endl;
    for (int i = 0; i < size; i++) {
        Node<Chain>* chain = table->GetListAt(i)->GetHead();

        while (chain != nullptr) {
            std::cout << "\t" << chain->data.key << std::endl;

            chain = chain->next;
        }
    }
}

void SearchByTag() {
    std::cout << "What tag to search:" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    
    Chain* searchChain = dm.SearchHashTable(line);

    if (searchChain == nullptr) {
        std::cout << "No tag \'" << line << "\' stored" << std::endl;
        return;
    }

    PrintTagTree(searchChain->value.GetRoot());
}

void PurgeOldTasks() {
    std::cout << "Are you sure? (y/n)" << std::endl;
    std::string choice;

    std::getline(std::cin, choice);

    if (choice == "y" || choice == "Y") {
        std::cout << "Purging Old Tasks" << std::endl;
        dm.PurgeTree();
        return;
    }

    std::cout << "Aborted Deletion of Old Tasks" << std::endl;
}

void Run(DataManager& loadDM, std::string fileName) {
    dm = loadDM;

    dm.Load(fileName);

    int choice = 0;
    std::string input;
    while (choice >= 0) {
        PrintMenu();
        std::getline(std::cin, input);
        choice = std::stoi(input);
        
        std::cout << std::endl;

        if (choice == 0) {
            Node<TasksList>* node = dm.GetRoot();
            if (node != nullptr) {
                PrintTaskTree(node);
            }
            else {
                std::cout << "No Tasks Have Been Added" << std::endl;
            }
        }
        else if (choice == 1) {
            AddTask();
        }
        else if (choice == 2) {
            RemoveTask();
        }
        else if (choice == 3) {
            UpdateTask();
        }
        else if (choice == 4) {
            Task* target = SearchForTask();
            
            if (target != nullptr) {
                PrintTask(target);
            }
        }
        else if (choice == 5) {
            RemoveWholeDate();
        }
        else if (choice == 6) {
            PrintAllTags();
        }
        else if (choice == 7) {
            SearchByTag();
        }
        else if (choice == 8) {
            PurgeOldTasks();
        }
        else {
            choice = -1;
        }

        std::cout << std::endl;
        for (int i = 0; i < 40; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    dm.Save(fileName);
}

#endif