#pragma once
#include <stdbool.h>

// Двоичное дерево поиска, из корня и количества узлов
typedef struct BST {
    struct Node* root;
    int countNodes;
} BST;

// Создание дерева, инициализация 0-ми
BST* createTree(void);

// Вставка элемента по значению, если уже есть, то не вставляем
void bstInsert(BST*, int);

// Проверка наличия элемента по значению
bool bstContains(BST*, int);

// Освобождение памяти, через освобождение всех веток
void bstFree(BST*);
