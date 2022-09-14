#ifndef CLI_H
#define CLI_H

#include <iostream>
#include "DataManager.h"

DataManager dm;

void PrintLinkedList(Node<Task>* node) {
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
    std::cout << node->data.key << std::endl;
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
        std::cout << i << " - " <<  *array[i] << endl;
    }
}

// Takes in int&, Returns Array of Tasks
Task** SearchTask(int& size) {
    std::cout << "Date of Task (mm/dd/yyyy)" << std::endl;
    int month, day, year;
    std::cout << "Month: ";
    cin >> month;
    std::cout << "Day: ";
    cin >> day;
    std::cout << "Year: ";
    cin >> year;
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

    cin.clear();

    return taskArray;
}

void EditTask(Task* ptr) {
    std::cout << "Editing: " << ptr->GetName() << std::endl;
    std::cout << "Due Date: " << ptr->GetDueDate() << std::endl;
    std::cout << "Notes: " << ptr->GetNotes() << std::endl;

    int choice = 0;
    while (choice >= 0) {    
        std::cout << "0 - Name" << std::endl;
        std::cout << "1 - Due Date" << std::endl;
        std::cout << "2 - Notes" << std::endl;
        std::cout << "-1 - Exit" << std::endl;

        cin >> choice;

        string line;
        
        // Clearing whitespace
        std::getline(cin, line);
        
        // Change Name
        if (choice == 0) {
            std::cout << "New Name: ";
            std::getline(cin, line);
            ptr->SetName(line);

            std::cout << std::endl;
        }
        // Change DueDate
        else if (choice == 1) {
            int in;
            int dueDate;
            std::cout << "New Due Date: " << std::endl;

            std::cout << "Month: ";
            cin >> in;
            dueDate = in * 100;

            std::cout << "Day: ";
            cin >> in;
            dueDate += in;

            std::cout << "Year: ";
            cin >> in;
            dueDate += in * 10000;

            ptr->SetDueDate(dueDate);
        }
        // Change Notes
        else if (choice == 2) {

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
    std::cout << "-1 - Exit" << std::endl;
}

void AddTask() {
    string name = "";
    int dueDate = -1;
    string notes = "";

    std::cout << "Name of Task: ";
    getline(cin, name);


    string temp;
    int month, day, year;
    std::cout << "Due Date of Task (mm/dd/yyyy)" << std::endl;
    std::cout << "Month: ";
    cin >> month;
    std::cout << "Day: ";
    cin >> day;
    std::cout << "Year: ";
    cin >> year;
    std::cout << std::endl;

    dueDate = year * 10000 + month * 100 + day;
    // TODO Date Verification

    getline(cin, temp); // Clearing Whitespace


    std::cout << "Notes: " << std::endl;
    getline(cin, notes);


    Task newTask(name, dueDate, notes);
    dm.AddTask(newTask);
}

void RemoveTask() {
    int size;
    Task** array = SearchTask(size);
    if (array == nullptr) {
        return;
    }

    int index;

    PrintTaskArray(array, size);
    std::cout << "Which index to Remove: ";
    cin >> index;
    
    Task* toRemove = array[index];
    
    dm.RemoveTask(toRemove);
}

void UpdateTask() {
    int size;
    Task** array = SearchTask(size);
    if (array == nullptr) {
        return;
    }

    int index;

    PrintTaskArray(array, size);
    std::cout << "Which index to Update: ";
    cin >> index;

    Task* editting = array[index];
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

void PrintTask() {
    int size;
    Task** array = SearchTask(size);
    if (array == nullptr) {
        return;
    }

    int index;

    PrintTaskArray(array, size);
    std::cout << "Which index to Print: ";
    cin >> index;

    Task* toPrint = array[index];

    std::cout << "Task Name: " << toPrint->GetName() << std::endl;
    std::cout << "Due Date: " << toPrint->GetDueDate() << std::endl;
    std::cout << "Notes: " << toPrint->GetNotes() << std::endl; 
}

void Run(DataManager& loadDM) {
    dm = loadDM;

    int choice = 0;
    string cleaner;
    while (choice >= 0) {
        PrintMenu();
        cin >> choice;
        getline(cin, cleaner); // Whitespace clear

        if (choice == 0) {
            PrintTaskTree(dm.GetRoot());
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
            PrintTask();
        }
        else {
            choice = -1;
        }
    }
}

#endif