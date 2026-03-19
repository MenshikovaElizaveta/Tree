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

// Рекурсивная функция прямого обхода
int bstPreorderIn(Node* curNode);

// Рекурсивная функция симметричного обхода
int bstInorderIn(Node* curNode);

// Рекурсивная функция обратного обхода
int bstPostorderIn(Node* curNode);

// Рекурсивная функция для получения высоты ветки
int branchHeight(Node* root);

// Рекурсивная функция для получения самого левого узла
int findLeftmost(Node* node);

// Рекурсивная функция для получения самого правого узла
int findRightmost(Node* node);
