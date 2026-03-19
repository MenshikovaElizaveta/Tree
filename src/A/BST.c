#include "BST.h"
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

int bstPreorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    printf("%d ", curNode->value);
    bstPreorderIn(curNode->leftChild);
    bstPreorderIn(curNode->rightChild);
    return 0;
}

int bstInorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    bstInorderIn(curNode->leftChild);
    printf("%d ", curNode->value);
    bstInorderIn(curNode->rightChild);
    return 0;
}

int bstPostorderIn(Node* curNode) // NOLINT(misc-no-recursion)
{
    if (curNode == NULL)
        return 1;

    bstPostorderIn(curNode->leftChild);
    bstPostorderIn(curNode->rightChild);
    printf("%d ", curNode->value);
    return 0;
}

int branchHeight(Node* root) // NOLINT(misc-no-recursion)
{
    if (root == NULL) {
        return 0;
    }

    int leftHeight = branchHeight(root->leftChild);
    int rightHeight = branchHeight(root->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int findLeftmost(Node* node)
{
    while (node->leftChild != NULL) {
        node = node->leftChild;
    }
    return node->value;
}

int findRightmost(Node* node)
{
    while (node->rightChild != NULL) {
        node = node->rightChild;
    }
    return node->value;
}
