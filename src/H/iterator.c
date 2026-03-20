#include "iterator.h"
#include "../A/BST.h"
#include "bypass.h"
#include <stdio.h>

typedef struct StackNode {
    Node* treeNode;
    struct StackNode* next;
} StackNode;

typedef struct Iterator {
    StackNode* stackTop;
    Node* current;
} Iterator;

Iterator* iteratorInit(BST* tree)
{
    if (tree == NULL) {
        printf("Дерево не существует.\n");
        return NULL;
    }

    Iterator* it = malloc(sizeof(Iterator));
    if (it == NULL)
        return NULL;

    it->stackTop = NULL;
    it->current = tree->root;

    return it;
}

bool iteratorHasNext(Iterator* it)
{
    return it->stackTop != NULL || it->current != NULL;
}

int iteratorNext(Iterator* it)
{
    if (it->stackTop == NULL && it->current == NULL) {
        printf("Ошибка: итератор исчерпан\n");
        return -1;
    }

    while (it->current != NULL) {
        StackNode* node = malloc(sizeof(StackNode));
        if (node == NULL) {
            printf("Ошибка выделения памяти.\n");
            iteratorFree(it);
            return -1;
        }
        node->treeNode = it->current;
        node->next = it->stackTop;

        it->stackTop = node;
        it->current = it->current->leftChild;
    }

    StackNode* top = it->stackTop;
    Node* node = top->treeNode;
    it->stackTop = top->next;
    free(top);

    it->current = node->rightChild;
    return node->value;
}

void iteratorFree(Iterator* it)
{
    if (it == NULL)
        return;

    while (it->stackTop != NULL) {
        StackNode* current = it->stackTop;
        it->stackTop = it->stackTop->next;
        free(current);
    }
    free(it);
}
