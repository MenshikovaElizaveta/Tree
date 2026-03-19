#include "statistics.h"
#include "BST.h"
#include <limits.h>
#include <stdio.h>

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

    return findLeftmost(curNode);
}

int bstMax(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Максимального значения нет./n");
        return INT_MAX;
    }

    Node* curNode = tree->root;

    return findRightmost(curNode);
}
