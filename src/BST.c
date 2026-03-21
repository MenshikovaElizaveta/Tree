#include "BST.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

BST* createTree(void)
{
    BST* tree = malloc(sizeof(BST));
    if (tree) {
        tree->root = NULL;
        tree->countNodes = 0;
    }
    return tree;
}

void bstInsert(BST* tree, int value)
{
    if (tree == NULL) {
        printf("Error: Tree is NULL\n");
        return;
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
        tree->countNodes++;
        return;
    }

    Node* current = tree->root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (value < current->value) {
            current = current->leftChild;
        } else if (value > current->value) {
            current = current->rightChild;
        } else {
            free(newNode);
            return;
        }
    }

    newNode->parent = parent;
    if (value < parent->value) {
        parent->leftChild = newNode;
    } else {
        parent->rightChild = newNode;
    }
    tree->countNodes++;
}

bool bstContains(BST* tree, int value)
{
    if (tree == NULL) {
        printf("Error: Tree is NULL\n");
        return false;
    }

    Node* current = tree->root;
    while (current != NULL) {
        if (current->value == value) {
            return true;
        } else if (value < current->value) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }
    return false;
}

static void freeSubtree(Node* node) // NOLINT(misc-no-recursion)
{
    if (node == NULL) {
        return;
    }

    freeSubtree(node->leftChild);
    freeSubtree(node->rightChild);

    free(node);
}

void bstFree(BST* tree)
{
    if (tree == NULL) {
        return;
    }
    freeSubtree(tree->root);
    tree->root = NULL;
    tree->countNodes = 0;
}

static int bstPreorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    printf("%d ", curNode->value);
    bstPreorderIn(curNode->leftChild);
    bstPreorderIn(curNode->rightChild);
    return 0;
}

int bstPreorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Пустое дерево\n");
        return 1;
    }

    bstPreorderIn(tree->root);
    return 0;
}

static int bstInorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    bstInorderIn(curNode->leftChild);
    printf("%d ", curNode->value);
    bstInorderIn(curNode->rightChild);
    return 0;
}

int bstInorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Пустое дерево\n");
        return 1;
    }

    bstInorderIn(tree->root);
    return 0;
}

static int bstPostorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    bstPostorderIn(curNode->leftChild);
    bstPostorderIn(curNode->rightChild);
    printf("%d ", curNode->value);
    return 0;
}

int bstPostorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Пустое дерево\n");
        return 1;
    }

    bstPostorderIn(tree->root);
    return 0;
}

static int branchHeight(Node* root) // NOLINT(misc-no-recursion)
{
    if (root == NULL) {
        return 0;
    }

    int leftHeight = branchHeight(root->leftChild);
    int rightHeight = branchHeight(root->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int bstHeight(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }

    return branchHeight(tree->root);
}

int bstSize(BST* tree)
{
    if (tree == NULL) {
        return 0;
    }

    return tree->countNodes;
}

int bstMin(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Минимального значения нет./n");
        return INT_MIN;
    }

    struct Node* curNode = tree->root;

    while (curNode->leftChild != NULL) {
        curNode = curNode->leftChild;
    }
    return curNode->value;
}

int bstMax(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Максимального значения нет./n");
        return INT_MAX;
    }

    Node* curNode = tree->root;

    while (curNode->rightChild != NULL) {
        curNode = curNode->rightChild;
    }
    return curNode->value;
}

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
