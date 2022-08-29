#include <iostream>
#include <sstream>

#include "Classes/TaskTree.h"

using namespace std;

template <class T>
void PrintTaskTree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    PrintTaskTree(node->left);

    cout << node->data << endl;

    PrintTaskTree(node->right);
}

template <class T>
void PrintLinkedList(Node<T>* node) {
    while (node != nullptr) {
        cout << node->data << endl;

        node = node->next;
    }
}

int main(int argc, char* argv []) {
    TaskTree* tree = new TaskTree();

    Task t1("test one", 2019);
    Task t2("test two", 2019);
    Task t3("test three", 10);

    Task* ptr1 = tree->Insert(t1);
    Task* ptr2 = tree->Insert(t2);
    Task* ptr3 = tree->Insert(t3);

    LinkedList<Task>* list = tree->Search(ptr2->GetDueDate())->GetList();

    tree->RemoveTask(ptr1);
    tree->RemoveTask(ptr2);

    TasksList* t = tree->Search(ptr2->GetDueDate());

    list = tree->Search(ptr2->GetDueDate())->GetList();

    PrintLinkedList(list->GetHead());

    return 0;
}