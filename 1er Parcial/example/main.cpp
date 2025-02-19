/*
AUTOR:      Luis Villalobos
CURSO:      Estructura de Datos
PROGRAMA:   Sort Algorithms
FECHA:      29 de marzo del 2023
*/

#include <iostream>
#include <time.h>
#include <string>
#include <iostream>
#include "sort.hpp"

int *create(int n)
{

    int *p = new int[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = rand() % (10 * n) + 1;
    }
    return p;
}

void print(int *a, int n)
{

    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%i ", a[i]);
    }
    printf("]\n");
}

int main(int argc, char const *argv[])
{

    srand((unsigned(time(nullptr))));

    int n;
    char option;
    string s;
    string number;

    getline(cin >> ws, s);
    for (int i = 0; i < s.length(); i++)
    {
        if(s[i] != ' '){
            number += s[i];
            continue;
        }
        option = s[i + 1];
        break;
    }
    
    n = stoi(number);

    int *a = create(n);
    printf("\nArray: \n");
    print(a, n);

    switch (option)
    {
    case 'Q':
        printf("Qsorted array: \n");
        Sort::quick(a, 0, (n - 1));
        break;
    case 'M':
        printf("Mergesorted array: \n");
        Sort::merge(a, 0, n - 1);
        break;
    case 'H':
        printf("Heapsorted array: \n");
        Sort::heap(a, n);
        break;
    default:
        break;
    }

    print(a, n);

    delete[] a;

    return 0;
}