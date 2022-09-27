#ifndef CLI_H
#define CLI_H

#include <iostream>

#include "DataManager.h"

DataManager dm;

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

// Takes in int&, Returns Array of Tasks
Task** SearchTasksList(int& size) {
    std::cout << "Date of Task (mm/dd/yyyy)" << std::endl;
    int month, day, year;
    std::cout << "Month: ";
    std::cin >> month;
    std::cout << "Day: ";
    std::cin >> day;
    std::cout << "Year: ";
    std::cin >> year;
    std::cout << std::endl;

    int searchDate = year * 10000 + month * 100 + day;
    
    TasksList* tasks = dm.SearchTree(searchDate);
    if (tasks == nullptr) {
        printf("No Task with Date: %i/%i/%i\n", month, day, year);
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

        std::cin >> choice;

        std::string line;
        
        // Clearing whitespace
        std::getline(std::cin, line);
        
        // Change Name
        if (choice == 0) {
            std::cout << "New Name: ";
            std::getline(std::cin, line);
            ptr->SetName(line);

            std::cout << std::endl;
        }
        // Change DueDate
        else if (choice == 1) {
            int in;
            int dueDate;
            std::cout << "New Due Date: " << std::endl;

            std::cout << "Month: ";
            std::cin >> in;
            dueDate = in * 100;

            std::cout << "Day: ";
            std::cin >> in;
            dueDate += in;

            std::cout << "Year: ";
            std::cin >> in;
            dueDate += in * 10000;

            ptr->SetDueDate(dueDate);
        }
        // Change Notes
        else if (choice == 2) {

        }
        // Add Tag(s)
        else if (choice == 3) {
            std::cout << "New Tags: (leave blank to stop)" << std::endl;
            
            std::getline(std::cin, line);
            while (line != "") {
                ptr->AddTag(line);

                std::getline(std::cin, line);
            }
        }
        // Remove Tag(s)
        else if (choice == 4) {
            if (ptr->GetTags()->GetHead() == nullptr) {
                std::cout << "Task Has No Tags" << std::endl;
                continue;
            }

            std::cout << "Current Tags: " << std::endl;
            PrintLinkedList(ptr->GetTags()->GetHead());

            std::cout << "Tags to Remove: (leave blank to stop)" << std::endl; 
            std::getline(std::cin, line);
            while(line != "") {
                ptr->RemoveTag(line);

                std::getline(std::cin, line);
            }
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
    std::cout << "-1 - Exit" << std::endl;
}

// Function takes user input and creates a new task
void AddTask() {
    std::string name = "";
    int dueDate = -1;
    std::string notes = "";

    std::cout << "Name of Task: ";
    std::getline(std::cin, name);

    
    // Date Parsing
    std::string temp;
    int month, day, year;
    std::cout << "Due Date of Task (mm/dd/yyyy)" << std::endl;
    std::cout << "Month: ";
    std::cin >> month;
    std::cout << "Day: ";
    std::cin >> day;
    std::cout << "Year: ";
    std::cin >> year;
    std::cout << std::endl;

    dueDate = year * 10000 + month * 100 + day;
    // TODO Date Verification

    std::getline(std::cin, temp); // Clearing Whitespace


    std::cout << "Notes: " << std::endl;
    std::getline(std::cin, notes);

    Task newTask(name, dueDate, notes);
    
    // Tags Input
    std::cout << "Tags: (leave blank to stop)" << std::endl;
    std::getline(std::cin, temp);
    while (temp != "") {
        newTask.AddTag(temp);

        std::getline(std::cin, temp);
    }

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
    std::cout << "Date of Task (mm/dd/yyyy)" << std::endl;
    int month, day, year;
    std::cout << "Month: ";
    std::cin >> month;
    std::cout << "Day: ";
    std::cin >> day;
    std::cout << "Year: ";
    std::cin >> year;
    std::cout << std::endl;

    int deleteDate = year * 10000 + month * 100 + day;

    dm.DeleteTasksList(deleteDate);
}

void Run(DataManager& loadDM, std::string fileName) {
    dm = loadDM;

    dm.Load(fileName);

    int choice = 0;
    std::string cleaner;
    while (choice >= 0) {
        PrintMenu();
        std::cin >> choice;
        std::getline(std::cin, cleaner); // Whitespace clear
        
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
            PrintTask(target);
        }
        else if (choice == 5) {
            RemoveWholeDate();
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