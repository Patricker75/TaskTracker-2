#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <sstream>
#include <fstream>
#include <iostream>

#include "Classes/TaskTree.h"
#include "Classes/Queue.h"

// Save/Load Data in .json format

std::string Indenter(int tabCount) {
    std::stringstream tabs;

    for (int i = 0; i < tabCount; i++) {
        tabs << "\t";
    }

    return tabs.str();
}

Task ParseTask(std::ifstream& file, int dueDate) {
    std::string line;

    std::string name;
    std::string notes;

    std::getline(file, line);
    name = line.substr(line.find(":") + 3);
    name = name.substr(0, name.find("\""));

    std::getline(file, line);
    notes = line.substr(line.find(":") + 3);
    notes = notes.substr(0, notes.find("\""));

    Task newTask(name, dueDate, notes);

    // TODO Implement Tag Parsing

    // Ignoring }
    std::getline(file, line);

    return newTask;
}

void ParseTreeNode(std::ifstream& file, TaskTree& tree) {
    std::string line;

    // Parsing TasksList
    // Order: dueDate -> Each Task
    std::getline(file, line);
    int dueDate = std::stoi(line.substr(line.find(" ") + 1, 8));

    // Ignoring \"tasks\": [ & {
    std::getline(file, line);
    std::getline(file, line);

    while (line.find("]") == line.npos) {
        Task t = ParseTask(file, dueDate);
        tree.Insert(t);

        std::getline(file, line);
    }
    
    // Clears the }
    std::getline(file, line);
}

TaskTree LoadData(std::string fileName) {
    std::ifstream file(fileName);
    std::string line;

    if (!file.good()) {
        return TaskTree();
    }

    // Ignoring the first two lines
    std::getline(file, line);
    std::getline(file, line);

    // Ignoring { & Priming ParseTreeNode
    std::getline(file, line);

    TaskTree tree;
    while(line.find("]") == line.npos) {
        ParseTreeNode(file, tree);

        std::getline(file, line);
    }

    return tree;
}

void SaveData(std::string fileName, TaskTree& tree) {
    std::ofstream file(fileName);
    int indentCount = 0;

    file << "{" << std::endl;
    indentCount++;

    file << Indenter(indentCount) << "\"tree\": [" << std::endl;
    indentCount++;

    Queue<Node<TasksList>*> nodeQueue;

    Node<TasksList>* listNode = tree.GetRoot();

    if (listNode != nullptr) {
        nodeQueue.Enqueue(listNode);
    }
    
    // Loop to print every TreeNode
    while (!nodeQueue.IsEmpty()) {
        listNode = nodeQueue.Dequeue();
        
        // Adding listNode's left and right
        if (listNode->left != nullptr) {
            nodeQueue.Enqueue(listNode->left);
        }
        if (listNode->right != nullptr) {
            nodeQueue.Enqueue(listNode->right);
        }

        file << Indenter(indentCount) << "{" << std::endl;
        indentCount++;

        int dueDate = listNode->data.key;
        file << Indenter(indentCount) << "\"dueDate\": " << dueDate << "," << std::endl;
        
        file << Indenter(indentCount) << "\"tasks:\": [" << std::endl;
        indentCount++;

        Node<Task>* taskNode = listNode->data.value.GetHead();

        // Loop to print every task in a TreeNode
        while (taskNode != nullptr) {
            file << Indenter(indentCount) << "{" << std::endl;
            indentCount++;

            Task task = taskNode->data;

            // Printing task's details (name, notes, tags)
            file << Indenter(indentCount) << "\"name\": " << "\"" << task.GetName() << "\"," << std::endl;
            file << Indenter(indentCount) << "\"notes\": " << "\"" << task.GetNotes() << "\"" << std::endl;
            
            // TODO Implement Saving Tags
            

            indentCount--;
            file << Indenter(indentCount) << "}";
            if (taskNode->next != nullptr) {
                file << ",";
            }
            file << std::endl;

            taskNode = taskNode->next;
        }
        indentCount--;

        file << Indenter(indentCount) << "]" << std::endl;
        indentCount--;

        file << Indenter(indentCount) << "}";
        if (!nodeQueue.IsEmpty()) {
            file << ",";
        }
        file << std::endl;


    }
    indentCount--;

    file << Indenter(indentCount) << "]" << std::endl;
    indentCount--;

    file << "}";

    file.flush();
    file.close();
}

#endif