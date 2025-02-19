/*
AUTOR:      Luis Villalobos
CURSO:      Estructura de Datos
PROGRAMA:   Dynamic Queue
FECHA:      21 de febrero del 2023
*/

#ifndef heap_hpp
#define heap_hpp

#include <assert.h>
#include <iostream>

using namespace std;

class Heap
{

    int *list;
    int s;
    int n;

    int left(int i) { return i * 2 + 1; };
    int right(int i) { return i * 2 + 2; };
    int parent(int i) { return (i - 1) / 2 ; };

    void swap(int &a, int &b);
    int maxChild(int);

public:
    Heap(int);
    ~Heap();

    void insert(int);
    int takeOut();

    int size() const { return this->s; }
    int capacity() const { return this->n; }

    bool isEmpty() const { return this->s == 0; };
    bool isFull() const { return this->s == this->n; };

    void print();
};

#endif