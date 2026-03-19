#pragma once

#include "BST.h"

// высота дерева
int bstHeight(BST* tree);

// количество узлов
int bstSize(BST* tree);

// минимальное значение
// если дерево пустое, то возвращается INT_MIN и выводится сообщение
int bstMin(BST* tree);

// максимальное значение
// если дерево пустое, то возвращается INT_MAX и выводится сообщение
int bstMax(BST* tree);
