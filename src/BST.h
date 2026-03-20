#pragma once
#include <stdbool.h>

// Узел BST, объявлен для использования функциями и структурой
typedef struct Node Node;

// Двоичное дерево поиска, из корня и количества узлов
typedef struct BST {
    Node* root;
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

// Функция прямого обхода
int bstPreorder(BST* tree);

// Функция симметричного обхода
int bstInorder(BST* tree);

// Функция обратного обхода
int bstPostorder(BST* tree);

// Функция получения высоты дерева
int bstHeight(BST* tree);

// Функция получения количества узлов
int bstSize(BST* tree);

// Функция получения минимального значения
// если дерево пустое, то возвращается INT_MIN и выводится сообщение
int bstMin(BST* tree);

// Функция получения максимального значения
// Если дерево пустое, то возвращается INT_MAX и выводится сообщение
int bstMax(BST* tree);

// Функция слияния двух деревьев
BST* bstMerge(BST* tree1, BST* tree2);
