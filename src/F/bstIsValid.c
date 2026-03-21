#include "bstIsValid.h"
#include <stdlib.h>

bool bstIsValid(BST* tree)
{
    if (tree == NULL)
        return true;

    Iterator* it = iteratorInit(tree);
    if (it == NULL)
        return false;

    if (!iteratorHasNext(it)) {
        iteratorFree(it);
        return true;
    }

    int previousValue = iteratorNext(it);

    while (iteratorHasNext(it)) {
        int currentValue = iteratorNext(it);
        if (currentValue <= previousValue) {
            iteratorFree(it);
            return false;
        }
        previousValue = currentValue;
    }
    iteratorFree(it);
    return true;
}
