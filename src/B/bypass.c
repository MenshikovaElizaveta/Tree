#include "bypass.h"
#include "BST.h"
#include <stdio.h>

int bstPreorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Пустое дерево\n");
        return 1;
    }

    bstPreorderIn(tree->root);
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

int bstPostorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        printf("Пустое дерево\n");
        return 1;
    }

    bstPostorderIn(tree->root);
    return 0;
}
