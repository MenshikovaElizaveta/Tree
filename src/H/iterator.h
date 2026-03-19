#pragma once
#include "../A/BST.h"
#include <stdbool.h>

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
