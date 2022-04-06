#include "funkcje.h"

int main(int argc, const char * argv[])
{
    int X_Dest = N-1;
    int Y_Dest = M-1;
    //int nDepth = 6;

    if (argc != 2)
    {
        printf( "Nieprawidlowa liczba argumentow : %d", argc );
        system( "pause" );
        return 1;
    }
    printf( "%s\n", argv[1] );

    //int nRow = N;
    //int nCol = M;

   
    int** pDepthTab = createTab( N, M );
    if( pDepthTab == NULL )
    {
        printf( "Alokacja pamieci dla tablicy sie nie powiodla !\n" );
        system( "pause" );
        return 2;
    }

    if( !readDepthTab( argv[1], pDepthTab, N, M ) )
    {
        printf( "Nie udalo sie otworzyc pliku !\n" );
        system( "pause" );
        return 3;
    }
    printf(" Wydruk kontrolny wczytanej tablicy pDepthTab\n");
    printTab( pDepthTab, N, M );


    int** pRoot = createTab( N, M );
    if( pRoot == NULL )
    {
        printf( "Alokacja pamieci dla tablicy sie nie powiodla !\n" );
        system( "pause" );
        return 4;
    }

    if( root( pDepthTab, N, M, SHIP_DEPTH, 0, 0, pRoot, X_Dest, Y_Dest ) )
    {
        printf( " Statek doplynal do portu\n " );
        printTab( pRoot, N, M );
    }
    else printf(" Statek nie doplynal do portu\n ");

    freeTab( &pDepthTab );
    freeTab( &pRoot );

    return 0;
}

