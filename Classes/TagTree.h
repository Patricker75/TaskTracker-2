#ifndef TAGTREE_H
#define TAGTREE_H

#include "TagsList.h"
#include "AVLTree.h"

class TagTree : public AVLTree<TagsList> {
public:
    TagTree() : AVLTree() {}
    
    void Insert(Task* ptr) {
        TagsList* list = this->Search(ptr);

        if (list == nullptr) {
            list = AVLTree::Insert(TagsList(ptr->GetDueDate()));
        }

        list->Insert(ptr);
    }

    TagsList* Search(Task* ptr) {
        return AVLTree::Search(TagsList(ptr->GetDueDate()));
    }

    void RemoveTask(Task* ptr) {
        if (ptr == nullptr) {
            return;
        }

        TagsList* listPtr = this->Search(ptr);

        if (listPtr == nullptr) {
            return;
        }

        listPtr->value.Delete(ptr);
        if (listPtr->value.Empty()) {
            AVLTree::Delete(*listPtr);
        }
    }

    bool Empty() {
        return this->root == nullptr;
    }
};

#endif