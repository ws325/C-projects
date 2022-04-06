#include "DStack.hpp"
#include <stdio.h>
#include <stdlib.h> //do funkcji free();
#include <memory.h>  //funkcji memset();
#include <float.h>  // potrzebny do DBL_MIN
using namespace std;

//DStackItem* pDStack = NULL;// czyscimy stos




//---------------------------------------------------------------------
void initDStack( DStackItem** pDStack)
{
    *pDStack = NULL;
}


//---------------------------------------------------------------------
void dEmptyStack( DStackItem** pDStack )
{
    while (!disEmpty( *pDStack )) ddel( pDStack );
}


//---------------------------------------------------------------------
void dpush( double d, DStackItem** pDStack )
{
    DStackItem* dptr = (DStackItem*)malloc(sizeof(DStackItem));// wskaznik pomocniczny
    if (!dptr)
    {
        perror("Allocation error !");
        return;
    }
    dptr->dKey = d;
    dptr->pdNext = *pDStack;
    *pDStack = dptr;
}


 //---------------------------------------------------------------------
double dpop( DStackItem** pDStack )
{
    if (!disEmpty( *pDStack ))
    {
        double d = dtop( *pDStack );
        ddel( pDStack );
        return d;
    }
    perror("Stack underflow !");
    return DBL_MIN;
}


 //---------------------------------------------------------------------
double dtop( DStackItem* pDStack )
{
    if ( !disEmpty( pDStack ) )
        return pDStack->dKey;
    perror("Stack underflow !");
    return DBL_MIN;
}



 //---------------------------------------------------------------------
void ddel( DStackItem** pDStack )
{
    if (!disEmpty( *pDStack ))
    {
        DStackItem* dptr = *pDStack;
        *pDStack = dptr->pdNext;
        free(dptr);//funkcja free(); sluzy do zwalniania pamieci
    }
    else perror("Stack underflow !");
}


 //---------------------------------------------------------------------
int disEmpty( DStackItem* pDStack ) // sprawdazam czy stos jest pusty
{
    return !pDStack;
}


