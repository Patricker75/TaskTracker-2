#include <iostream>
#include <sstream>

#include "DataManager.h"
#include "Queue.h"

#include "TagHashTable.h"

using namespace std;

static DataManager manager;

// Task List to String 
string ListToString(LinkedList<Task>* list) {
    stringstream out;

    // currentNode->key == currentTask
    Node<Task>* currentNode = list->GetHead();

    // Outputs Due Date
    out << currentNode->key.GetDueDate() << endl;

    while (currentNode != nullptr) {
        out << currentNode->key.GetName() << endl;

        currentNode = currentNode->next;
    }

    return out.str();
}

// Tag List to String
string ListToString(string tag, LinkedList<Task*>* list) {
    stringstream out;

    Node<Task*>* currentNode = list->GetHead();

    out << tag << endl;

    while (currentNode != nullptr) {
        out << currentNode->key->GetName() << endl;

        currentNode = currentNode->next;
    }

    return out.str();
}

template <class K, class V>
void PrintTaskTree(Node<K, V>* node) {
    if (node == nullptr) {
        return;
    }

    PrintTaskTree(node->left);

    cout << ListToString(node->value) << endl;

    PrintTaskTree(node->right);
}

void Run() {
    PrintTaskTree(manager.GetRoot());

    // string tag = "cheese eater";
    // LinkedList<Task*>* tagList = manager.SearchTag(tag);
    // cout << ListToString(tag, tagList) << endl;

    LinkedList<Task>* list = manager.SearchDate(6);
    int size = list->GetSize();
    Task* ptrArray[size];

    Node<Task>* currentNode = list->GetHead();

    for (int i = 0; i < size; i++) {
        ptrArray[i] = &currentNode->value;

        currentNode = currentNode->next;
    }
    
    for (int i = 0; i < size; i++) {
        cout << (i + 1) << " - " << ptrArray[i]->GetName() << endl;
    }
}

int main(int argc, char* argv []) {
    Task t1("test", 6);
    Task t2("testing", 6);
    Task t3("bing chilling", 1);
    
    t1.AddTag("testing");
    t2.AddTag("cheese eater");
    t3.AddTag("testing");
    t3.AddTag("cheese eater");

    manager.AddTask(t1);
    manager.AddTask(t2);
    manager.AddTask(t3);

    Run();

    return 0;
}