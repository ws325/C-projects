#ifndef STACK_H
#define STACK_H

#include <stdio.h>



typedef struct StackItem //definicja struktury
{
    char       cKey;
    StackItem* pNext;
}StackItem;



// stos znakowy
void initStack( StackItem** pStack ); //Stack
void EmptyStack( StackItem** pStack ); //dwie gwiazdki bo chcemy zmioenic adres
void push( char c, StackItem** pStack );
char pop( StackItem** pStack );
char top( StackItem* pStack );
void del( StackItem** pStack );
int isEmpty( StackItem* pStack );




#endif

