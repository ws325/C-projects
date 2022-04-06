#include "Stack.hpp"
#include <stdio.h>
#include <memory.h>
#include <cstdlib>
using namespace std;

//StackItem* pStack = NULL; // czyscimy stos //pStack zmienna globalna



//---------------------------------------------------------------------
void initStack( StackItem** pStack )
{
    *pStack = NULL;
}


//---------------------------------------------------------------------
void EmptyStack( StackItem** pStack )
{
    while(!isEmpty( *pStack )) del( pStack);
}


//---------------------------------------------------------------------
void push( char c, StackItem** pStack )
{
    StackItem* ptr = (StackItem*)malloc( sizeof( StackItem ) );
    if(!ptr) //sprawdza czy alkokacja sie powiodla
    {
        perror( "Allocation error !" );
        return;
    }
    
    ptr->cKey = c;
    ptr->pNext = *pStack;
    *pStack = ptr; //przypisujemy do pStack adres ostatnio zaalokowanego ptr
}


 //---------------------------------------------------------------------
char pop( StackItem** pStack )
{
    char c;
    if( c = top( *pStack ) )
    {
        del( pStack );
        return c;
    }
    perror("Stack underflow !");
    return 0;
}


 //---------------------------------------------------------------------
char top( StackItem* pStack )
{
    if(!isEmpty( pStack ))
        return pStack->cKey;//zwraca ostatnio polozony element na stosie
    return 0;
}


 //---------------------------------------------------------------------
void del( StackItem** pStack )
{
    if(!isEmpty( *pStack ))
    {
        StackItem* ptr = *pStack;
        *pStack = ptr->pNext; //pod pStack podstawiam adres "niszczonego" elementu
        free( ptr );//zwalniam obszar pamieci ktory wskazywala zmienna wskaznikowa ptr
    }
    else perror("Stack underflow !");
    
}

 //---------------------------------------------------------------------
int isEmpty( StackItem* pStack )
{
    return !pStack;
}


