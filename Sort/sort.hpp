#ifndef sort_hpp
#define sort_hpp
#include <stdio.h>
using namespace std;



//void createTab( int tab[] );
//void printTab( int tab[] );
void InsertionSort( int* tab, int nSize );
void SelectionSort( int* tab, int nSize );
void BubbleSort( int* tab, int nSize );
void ShakeSort( int* tab, int nSize );
void HalfInsertionSort( int* tab, int nSize );
void QuickSort( int* tab, int l , int p );
void Update( int* tab, int l, int p );
void QuickSortInterface(int *tab, int size);
void HeapSort( int* tab, int nSize );

#endif
