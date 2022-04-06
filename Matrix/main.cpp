#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define MIN 1.e-16

using namespace std;

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
void PrintVector( double* vector, int nSize );


int main(int argc, const char* argv[]) {

    // Obs³uga argumentów
#ifdef _DEBUG_
    printf( "Liczba argumentów %d\n", argc );
    for( int i = 0; i < argc; i++ )
    {
        printf( "Argument %d: %s\n", i, argv[i] );
    }
#endif
    if( argc != 2 )
    {
        printf( "Usage: %s <DATA_FILE>\n", argv[0] );
        system( "pause" );
        return 1;
    }

    FILE* fin = fopen( argv[1], "r" );
    if( !fin )   //sprawdzam czy plik zostal poprawnie otwarty
    {
        printf( "Nie udalo siê otworzyc pliku: %s\n", argv[1] );
        system( "pause" );
        return 2;
    }

    int size = 0;
    fscanf( fin, "%d", &size );
#ifdef _DEBUG_
    printf( "Rozmiar macierzy %d\n", size );
#endif

    double** matrix = NULL;
    double* vectorB = (double*)malloc( size * sizeof(double) );
    if( !CreateMatrix( &matrix, size ) || !vectorB )
    {
        printf( "Blad alokacji pamieci !\n" );
        system( "pause" );
        return 3;

    }
    memset(vectorB, 0, size * sizeof(double));
    //free(vectorB);

    ReadData( fin, matrix, vectorB, size );
    fclose( fin );


    #ifdef _DEBUG_
    printf( "Wczytane dane:" );
    printf( "Macierz A\n" );
    PrintMatrix( matrix, size );
    printf( "Wektor B\n" ); 
    PrintVector( vectorB, size );
    #endif

   
    double det = Det( matrix, size );
    if( fabs( det ) < MIN ) // niedokladnosc obliczeniowa //fabs(); wartosc bezwzgledna dla double
    {
        printf( "Macierz nie jest nieosobliwa !\n" );
        system( "pause" );
        return 4;
    }

    #ifdef _DEBUG_
    printf( "Det(A) = %lf\n", det );
    #endif

    // wykreowac wektor wynikowy
    double* vectorX = (double*)malloc( size * sizeof(double) );
    //memset(vectorX, 0, size * sizeof(double));
    // rozwiazac ukl
    double** matrixInv = NULL;
    //CreateMatrix(&matrixInv, size);
    if( !CreateMatrix( &matrixInv, size ) || !vectorX )
    {
        printf( "Blad alokacji pamieci !\n" );
        system( "pause" );
        return 5;
    }
    memset( vectorX, 0, size * sizeof(double) );

    InverseMatrix( matrixInv, matrix, size, det );
#ifdef _DEBUG_
    printf( "Inv Macierz A\n" );
    PrintMatrix( matrixInv, size );
#endif 
    LayoutEqu( matrixInv, vectorB, vectorX, size );

    // wyniki
    printf( "Wyniki:\n" );
    PrintVector( vectorX, size );

   // zwolnic pamiec  (usuwanie macierzy)!!!
    DeleteMatrix( &matrix, size );
    DeleteMatrix( &matrixInv, size );
    free( vectorB );
    free( vectorX );
    system( "pause" );
    
    return 0;
}



//------------------------------------------------------
void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
    for( int i = 0; i < nDim; i++ )
    {
        //double* col = *(pMatrix+i);//wskaznik pomocniczy do zmiany kolumn
        double* col = *pMatrix++;//wskaznik pomocniczy do zmiany kolumn

        for( int j = 0; j < nDim; j++ )
        {
            fscanf( fin, "%lf", col++ );
        }
        //fscanf(fin, "%lf", b + i );
        fscanf( fin, "%lf", b++ );
    }
}


//------------------------------------------------------
//drukuje wektor
void PrintVector( double* vector, int nSize )
{
    //double* printvX = vector;
    for( int i = 0; i < nSize; i++ )
    {
        printf( "x%d=%.2lf\n", i, *vector++ );
       //vector + 1;
       // printf( "x%d=%.2lf\n", i, *printvX );
       //printvX++;
    }
}
