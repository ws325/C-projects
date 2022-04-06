#include "funkcje.h"
#define _DEBUG_

//----------------------------------------------------------------------------
int readDepthTab( const char* sFile, int** pTab, int nRow, int nCol )
{
	FILE* file = fopen( sFile, "r" );

	if( !file )	return 0;
	
	for( int i = 0; i < nRow; i++ )
	{
		int* ptr = *pTab++;

		for( int j = 0; j < nCol; j++ )
		{
			fscanf( file, "%d", ptr++ );
		}

	}
	fclose( file );

	return 1;
}



//----------------------------------------------------------------------------
int** createTab( int nRow, int nCol )
{

	int* longArray = (int*)malloc( sizeof( int* ) * nRow * nCol );
	if( !longArray ) return NULL;

	memset( longArray, 0, sizeof( int* ) * nRow * nCol );


	int** pTab = (int**)malloc( sizeof( int* ) * nRow );
	if( !pTab )
	{
		free( longArray );
		return NULL;
	}
	memset( pTab, 0, nRow * sizeof( int* ) );


	int** temppTab = pTab;
	for( int i = 0; i < nRow; i++, temppTab++ )
	{
		//*(pTab + i) = longArray + i * nCol;
		*temppTab = longArray;
		longArray += nCol;
	}

	return pTab;
}



//----------------------------------------------------------------------------
void printTab( int** pRoot, int nRow, int nCol )
{
    for( int i = 0; i < nRow; i++ )   
    {
       
        int* ptr = *pRoot++;  

        for( int j = 0; j < nCol; j++ ) 
        {
            printf( "%d\t", *ptr++ ); 
           
        }
        printf( "\n" );
    }
    printf( "\n" );
}



//----------------------------------------------------------------------------
int move( int** pDepthTab, int nRow, int nCol, int nDepth, int nextMove, int x, int y, int* px, int* py, int** pRoot )
{
	switch( nextMove )
	{
	case UP: *px = x - 1; *py = y; break;

	case RIGHT: *px = x; *py = y + 1; break;

	case DOWN: *px = x + 1; *py = y; break;

	case LEFT: *px = x; *py = y - 1; break;
	}

	if( *px <= nRow && *py <= nCol && *px >= 0 && *py >= 0 )
		if( pRoot[*px][*py] == 0 && nDepth <= pDepthTab[*px][*py] ) return 1;

	return 0;
}



//----------------------------------------------------------------------------
int root( int** pDepthTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{

	static int moveCounter = 1;

#ifdef _DEBUG_
	printTab( pRoot, nRow, nCol );
	printf("\n");
#endif

	pRoot[x][y] = moveCounter++;

	if( x == x_dest && y == y_dest ) return 1;

	int px = 0;
	int py = 0;

	for( int moveDirection = UP; moveDirection <= LEFT; moveDirection++ )
	{
		if( move( pDepthTab, nRow, nCol, nDepth, moveDirection, x, y, &px, &py, pRoot ) )
		{
			//pRoot[px][py] = moveCounter++;
			if( root( pDepthTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) ) return 1;
		}
	}
	pRoot[x][y] = 0;
	moveCounter--;

	return 0;
}



//----------------------------------------------------------------------------
void freeTab( int*** pTab )
{
	free( **pTab );
	free( *pTab );
	pTab = NULL;

	/*
   int** ptab = *pTab;
	int* longarray = *ptab;
	free(longarray);
	free(ptab);
	*pTab = NULL;
	*/
}
