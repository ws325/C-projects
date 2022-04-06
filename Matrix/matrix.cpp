#include "matrix.h"

// wycina wiersz i kolumne z tab we pTabI i reszte kopiuje do
//tabl wyjsciowej pTabO
// nalezy uzyc dwa razu continue pomijajac wiersz nRow i kolumne nCol
void Complement(  double** pTabO, double** pTabI, int nRow, int nCol, int nDim );

// oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
void ComplMatrix( double** pTabD, double** pTab, int nDim ); //macierz dopelnien





//------------------------------------------------------
int CreateMatrix( double*** pTab, int nSize ) // kreowanie macierzy
{
    *pTab = (double**)malloc( sizeof(double*) * nSize );
    if( !pTab )
        return 0;

    memset( *pTab, 0, sizeof(double*) * nSize );

    double** p = *pTab;  // pomocniczy wskaznik do alokacji
    for( int i = 0; i < nSize; i++ )
    {
        *p = (double*)malloc( sizeof(double) * nSize );
        if( !*pTab ) return 0; 

        memset( *p++, 0, sizeof(double) * nSize );

    }
    return 1;
}

//------------------------------------------------------
void DeleteMatrix( double*** pMatrix, int nDim )
{
    double** v = *pMatrix;
    for( int i = 0; i < nDim; i++ )
        free( *v++ );
    free( *pMatrix );
    *pMatrix = NULL;
}


//------------------------------------------------------
//transponowanie macierzy
void TransMatrix( double** pTab, int nDim ) // bez pomocniczej, raz wolno indeksowac
{

    double** row = pTab;

    for( int i = 0; i < nDim - 1; i++, row++ ) 
    {
        // 0,0  1,1  2,2
        double* ptrElRow = *row + 1 + i;  //ptrElementRow // +1 po to zeby ustawic wskaznik na pierwszy element za przekontna
       
        for( int j = i + 1; j < nDim; j++ )
        {
            double temp = pTab[j][i];
            pTab[j][i] = *ptrElRow;
            *ptrElRow++ = temp;
            //*ptrElRow = temp; 
            //ptrElRow++;
        }
        //row++; 
    }
    //double** pT = pTab;

    //for (int i = 0; i < nDim - 1; i++)
    //{
    //    double* pom = *pT + i + 1; //bo w pêtli ni¿ej startujê od i+1, dlatego dodajê i+1
    //    for (int j = i + 1; j < nDim; j++) //i+1, bo nie ma potrzeby zamieniaæ elementów, dla których i=j
    //    {
    //        double a = *pom;
    //        *pom++ = pTab[j][i];
    //        pTab[j][i] = a;
    //    }
    //    pT++; //przejœcie tablicy pomocniczej pomT do kolejnego wiersza
    //}

}


//------------------------------------------------------
// wyznacznik rekurencyjnie
double Det( double** pTab, int nSize ) //rozwiniecie wzgl 0-go wiersza // dla 2x2 uzyc znanego wzoru - mozna zaindeksowac
{
 if( nSize == 1 ) return pTab[0][0];
 if( nSize == 2 ) return pTab[0][0]*pTab[1][1] - pTab[0][1]*pTab[1][0];
    
 double** matrix = NULL; //tablica pomocnicza do liczenia wyznacznika dopelnien
 //CreateMatrix( &matrix, nSize - 1 );
 if ( !CreateMatrix( &matrix, nSize - 1 ) )
 {
     printf( "Blad alokacji pamieci dla macierzy pomocniczej !\n" );
     system( "pause" );
     return 6;
 }

 double* ptr = *pTab; //wskaznik pomocniczy do przesuwania sie po zerowym wierszu
 double suma = 0;

    int sign = 1;

    for( int i = 0; i < nSize; i++ )
    {
        Complement( matrix, pTab, 0, i, nSize );
        suma += sign * *ptr++ * Det( matrix, nSize - 1 );
        sign = -sign;
    }
    DeleteMatrix( &matrix, nSize - 1 );  //usuwam niepotrzebna juz tablice pomocnicza
    return suma;
}



//------------------------------------------------------
// drukuje macierz
void PrintMatrix( double** pTab, int nSize )
{
    for( int i = 0; i < nSize; i++ )   
    {
        //double* ptr = *(pTab + i);  //wskaznik pomocniczy
        double* ptr = *pTab++;  //wskaznik pomocniczy
        for( int j = 0; j < nSize; j++ ) 
        {
            printf( "%.lf\t", *ptr++ ); //wskaznik ptr przesuwa sie po kolejnych kolunach
            //cout << pTab[i][j] << ' ';
           
        }
        printf( "\n" );
    }
    printf( "\n" );
}


//------------------------------------------------------
void Complement(  double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{
    
    //double** rowO = pTabO;
    //double** rowI = pTabI;
    for( int i = 0; i < nDim; i++, pTabI++ )
    {
        if( i == nRow ) continue;
        double* colO = *pTabO;
        double* colI = *pTabI;
        for( int j = 0; j < nDim; j++, colI++ )
        {
            if( j == nCol ) continue;
            *colO = *colI;
            colO++;
        }
       pTabO++;
    }
    /*
    double** rowO = pTabO;
    double** rowI = pTabI;
    for (int i = 0; i < nDim; i++, rowI++)
    {
        if( i == nRow ) continue;
        double* colO = *rowO;
        double* colI = *rowI;
        for( int j = 0; j < nDim; j++, colI++ )
        {
            if( j == nCol ) continue;
            *colO = *colI;
            colO++;
        }
        rowO++;
    } */
}


//------------------------------------------------------
// oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
void ComplMatrix( double** pTabD, double** pTab, int nDim )
{
    /*
    double** rowComp = pTabD;
    double** row = pTab;
    */

    double** matrix = NULL;
    //CreateMatrix( &matrix, nDim - 1 );
    if( !CreateMatrix( &matrix, nDim - 1 ) )
    {
        printf( "Blad alokacji pamieci dla macierzy pomocniczej !\n" );
        system( "pause" );
    }

    for( int i = 0; i < nDim; i++ ) //, rowComp++, row++ ) 
    {
        //double* colComp = *rowComp;
        //double* col = *row;

        double sign = (i % 2) ? -1 : 1;
        double* pD = *pTabD++;

        for( int j = 0; j < nDim; j++ ) //, colComp++, col++, sign = -sign)
        {
            //double** matrix;
            //CreateMatrix( &matrix, nDim - 1 );

            //col -= j;
            //row -= i;

            Complement( matrix, pTab, i, j, nDim );
            *pD++ = Det( matrix, nDim - 1 ) * sign;
            sign = -sign;
            //row += i;
            //col += j;

            //*colComp = sign * Det( matrix, nDim - 1 );
            //DeleteMatrix( &matrix, nDim - 1 );
        }
       // pTabD++;

    }
    DeleteMatrix( &matrix, nDim - 1 );
  
}


//------------------------------------------------------
// macierz odwrotna , na we obliczony wczesniej w main() det
void InverseMatrix( double** pInv, double** pTab, int nSize, double det )
{
    //double** matrix;
    //CreateMatrix( &matrix, nSize );
    ComplMatrix( pInv, pTab, nSize );
    #ifdef _DEBUG_
    printf( "ComplMatrix A\n" );
    PrintMatrix( pInv, nSize );
    #endif

    TransMatrix( pInv, nSize );
#ifdef _DEBUG_
    printf( "Trans Inv A\n" );
    PrintMatrix( pInv, nSize );
#endif

    //double** rowPtr = pInv;
    

    for( int row = 0; row < nSize; row++ ) //, rowPtr++ )
    {
        double* colPtr = *pInv++; //*rowPtr;

        for( int col = 0; col < nSize; col++, colPtr++ )
        {
            //double div = *colPtr / det;
            //*colPtr = div;
            *colPtr /= det;
        }
        //pInv++;
    }
    /*
    //TransMatrix( pInv, nSize );
#ifdef _DEBUG_
    printf("Trans Inv A\n");
    PrintMatrix(pInv, nSize);
#endif
    */
    //DeleteMatrix(&matrix, nSize);
}


//------------------------------------------------------
// rozwiazuje ukl rownan
void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize )
{
    //double** rowInv = pInv;
    //double* rowRes = pRes;
    
    //memset( pRes, 0, nSize * sizeof(double) );

    for( int i = 0; i < nSize; i++, pRes++, pInv++ ) // rowRes++ )
    {
        double* colInv = *pInv;
        double* rowB = pB;
        
        for( int j = 0; j < nSize; j++, colInv++, rowB++ )
        {
            /*
            double b = (*rowB);
            double inv = *colInv; 
            *rowRes += b * inv;
            */
            *pRes += (*colInv) * (*rowB);
        }
      
    }
    

    /*memset(pRes, 0, nSize * sizeof(double));
    for (int i = 0; i < nSize; i++, pInv++, pRes++)
    {
        for (int j = 0; j < nSize; j++, (*pInv)++, pB++)
        {
            double b = (*pB);
            double inv = **pInv;
            *pRes += b * inv;
        }
        pB -= nSize;
        *pInv -= nSize;
    }
    pInv -= nSize;
    pRes -= nSize;  */
}
