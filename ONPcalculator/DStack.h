#ifndef DSTACK_H  // musi byc unikalny
#define DSTACK_H
#include <stdio.h>

typedef struct DStackItem // definiuja struktury
{
    double dKey;
    DStackItem* pdNext;

}DStackItem;

// stos liczbowy
void initDStack( DStackItem** pDStack );
void dEmptyStack( DStackItem** pDStack );//czyszczenie stosu
void dpush( double c, DStackItem** pDStack );// wkladam na stos
double dpop( DStackItem** pDStack );//sciaganie ze stosu
double dtop( DStackItem* pDStack );// wartosc szczytu
void ddel( DStackItem** pDStack );// usuwam ze szczytu
int disEmpty( DStackItem* pDStack );//sprawdzam czy stos pusty

#endif

