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

void bstDelete(BST* tree, int value)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Error: Tree is NULL or empty\n");
        return;
    }

    Node* curNode = tree->root;

    while (curNode != NULL && curNode->value != value) {
        if (value < curNode->value) {
            curNode = curNode->leftChild;
        } else {
            curNode = curNode->rightChild;
        }
    }

    if (curNode == NULL) {
        printf("Value not found\n");
        return;
    } else if (curNode->leftChild != NULL && curNode->rightChild != NULL) {
        Node* replacement = curNode->rightChild;
        while (replacement->leftChild != NULL) {
            replacement = replacement->leftChild;
        }

        if (replacement->parent->leftChild == replacement) {
            replacement->parent->leftChild = replacement->rightChild;
        } else {
            replacement->parent->rightChild = replacement->rightChild;
        }

        if (replacement->rightChild != NULL) {
            replacement->rightChild->parent = replacement->parent;
        }

        curNode->value = replacement->value;
        curNode = replacement;
    } else if (curNode->leftChild != NULL) {
        curNode->leftChild->parent = curNode->parent;
        if (curNode == tree->root) {
            tree->root = curNode->leftChild;
        } else {
            curNode->parent->leftChild = curNode->leftChild;
        }
    } else if (curNode->rightChild != NULL) {
        curNode->rightChild->parent = curNode->parent;
        if (curNode == tree->root) {
            tree->root = curNode->rightChild;
        } else {
            curNode->parent->rightChild = curNode->rightChild;
        }
    } else {
        if (curNode == tree->root) {
            tree->root = NULL;
        } else if (curNode == curNode->parent->leftChild) {
            curNode->parent->leftChild = NULL;
        } else {
            curNode->parent->rightChild = NULL;
        }
    }

    free(curNode);
    tree->countNodes--;
}

static int inorderKth(Node* node, int k, int* count) // NOLINT(misc-no-recursion)
{
    if (node == NULL) {
        return -1;
    }
    int left = inorderKth(node->leftChild, k, count);
    if (left != -1) {
        return left;
    }
    (*count)++;
    if (*count == k) {
        return node->value;
    }
    return inorderKth(node->rightChild, k, count);
}

int bstKthMin(BST* tree, int k)
{

    if (tree == NULL || tree->root == NULL) {
        printf("Error: Tree is NULL or empty\n");
        return -1;
    }

    if (k <= 0) {
        printf("Error: k is less than one\n");
        return -1;
    } else if (k > tree->countNodes) {
        printf("Error: k increases the number of BST elements\n");
        return -1;
    } else {
        int count = 0;
        return inorderKth(tree->root, k, &count);
    }
}
