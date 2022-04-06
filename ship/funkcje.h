#ifndef funkcje_h
#define funkcje_h
#include <iostream>

#define N 8
#define M 8
#define SHIP_DEPTH 6


typedef enum
{
    UP = 1,
    RIGHT,
    DOWN,
    LEFT,
}Directions;

int move( int** pDepthTab, int nRow, int nCol, int nDepth, int nextMove, int x, int y, int* px, int* py, int** pRoot );

int root( int** pDepthTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );

int readDepthTab( const char* sFile, int** pTab, int nRow, int nCol );

int** createTab( int nRow, int nCol );

void printTab( int** pRoot, int nRow, int nCol );

void freeTab( int*** pTab );


#endif