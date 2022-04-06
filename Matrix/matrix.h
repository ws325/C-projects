#ifndef matrix_h
#define matrix_h
#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <stdio.h>

#define _DEBUG_
using namespace std;

int CreateMatrix( double*** pTab, int nSize );   //!!!!!  0 error  1 -ok
void DeleteMatrix( double*** pTab, int nSize );  // *pTab==NULL

//transponowanie macierzy
void TransMatrix( double** pTab, int nDim ); // bez pomocniczej, raz wolno indeksowac

// macierz odwrotna , na we obliczony wczesniej w main() det
void InverseMatrix( double** pInv, double** pTab, int nSize, double det );

// wysnacznik rekurencyjnie
double Det( double** pTab, int nSize ); //rozwiniecie wzgl 0-go wiersza
// dla 2x2 uzyc znanego wzoru - mozna zaindeksowac

// rozwiazuje ukl rownan
void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize );

// drukuje macierz
void PrintMatrix( double** pTab, int nSize );


#endif
