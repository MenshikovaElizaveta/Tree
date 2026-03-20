#include "BST.h"

#include <stdio.h>

int main(void)
{
    BST* tree = createTree();
    bstInsert(tree, 5);
    bstInsert(tree, 3);
    bstInsert(tree, 4);
    bstInsert(tree, 6);
    bstInsert(tree, 8);

    printf("Contains 4: %s\n", bstContains(tree, 4) ? "true" : "false");
    printf("Contains 10: %s\n", bstContains(tree, 10) ? "true" : "false");

    bstFree(tree);
    return 0;
}
