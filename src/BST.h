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

// узел стека для нерекурсивного обхода дерева
// стек реализован в виде односвязного списка
typedef struct StackNode StackNode;

// итератор хранит стек узлов и текущий узел для обхода
typedef struct Iterator Iterator;

// создание итератора
// возвращает указатель на итератор или NULL при ошибке
Iterator* iteratorInit(BST* tree);

// true, если в дереве есть непосещённые узлы, иначе - false
bool iteratorHasNext(Iterator* it);

// возвращает значение следующего узла. Если итератор исчерпан, то -1
int iteratorNext(Iterator* it);

// освобождение памяти
void iteratorFree(Iterator* it);
