#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "sort.hpp"
#define _DEBUG_
using namespace std;

clock_t start, stop;
//double timeSort;

int* createTab( int nSize );
void randomTab( int* tab, int nSize );
void printTab( int* tab, int nSize );
typedef void (*sortPtr)( int*, int );
void printTestTab( int* tab, int nSize );


int main(int argc, const char * argv[]) {
 
    if( argc != 2 )
    {
        printf( "Zla liczba argumentow %d ", argc);
        //system( "pause" );
        return 1;
    }
    
   int size = atoi( argv[1] ); //wczytuje rozmiar tablicy zmieniajac z char na int - atoi();
    
    sortPtr pSortTab[] = { InsertionSort, ShakeSort, BubbleSort, SelectionSort, HalfInsertionSort,
                            QuickSortInterface, HeapSort };
    

    char* tabNames[] = { "InsertionSort", "ShakeSort", "BubbleSort", "SelectionSort", "HalfInsertionSort",                          "QuickSort", "HeapSort" };
    
    int* mainArray = createTab(size);
    int* cloneArray = createTab(size);
    randomTab(mainArray, size);
    
    #ifdef _DEBUG_
    printf( "Wejsciowa tablica" );
        printTab( mainArray, size );
        printf( "\n\n" );
    #endif
    
    
    if( mainArray == NULL || cloneArray == NULL )
    {
        printf( "Blad alokacji pamieci dla tablicy !\n" );
        //system( "pause" );
        return 2;
    }
    
    
    
    for( int i = 0; i < sizeof( pSortTab )/sizeof( void* ); i++ )
    {
       
        printf( "Funkcja: %s", tabNames[i] );
        memcpy( cloneArray, mainArray, sizeof( int ) * size );
        start = clock();
        pSortTab[i]( cloneArray, size );
        stop = clock();
        #ifdef _DEBUG_
        printTestTab( cloneArray, size );
        #endif
        double timeSort = (double)(stop-start) / CLOCKS_PER_SEC;
        printf( "   sort time = %.10lf", timeSort );
        printf( "\n\n" );
    }
    
    
    free( mainArray );
    free( cloneArray );
   
    return 0;
}





int* createTab( int nSize )
{
    int* tab = (int*)malloc( nSize * sizeof( int ) );
    if( !tab ) // *tab != NULL
     {
       perror( "Blad alokacji pamieci !\n" );
       return NULL; // niepowodzenie
     }
    memset( tab, 0, nSize * sizeof( int ) );
    return tab;
}

void randomTab( int* tab, int nSize )
{
    srand( time( NULL ) );
    for( int i = 0; i < nSize; i++ ) *tab++ = rand()%10;
}

void printTab( int* tab, int nSize )
{
    for( int i = 0; i < nSize; i++ )
    {
        if( i % 10 == 0 ) printf("\n" );
               printf( "%d ", *tab++ );
    }
    printf("\n");
}


void printTestTab( int* tab, int nSize )
{
    for( int i = 0; i < nSize/2; i++ )
    {
        if( i % 10 == 0 ) printf("\n" );
        printf( "%d ", *tab++ );
    }
}
