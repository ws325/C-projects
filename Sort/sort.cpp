#include "sort.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;
#define MAX 10



void InsertionSort( int* tab, int nSize )
{
    
    for( int i = 1; i < nSize; i++ )
    {
        int x = tab[i];
        int j = i - 1;
        
        while( x < tab[j]  && j >= 0 )
        {
            tab[j+1] = tab[j];
            j = j - 1;
        }
        tab[j+1] = x;
    }
}



void SelectionSort( int* tab, int nSize )
{
    for( int i = 0; i < nSize - 1; i++ )
        {
            int min = tab[i];
            int ix = i;
    
            for( int j = i + 1; j < nSize; j++ )
            {
                if( tab[j] < min )
                {
                    min = tab[j];
                    ix = j;
                }
            }
            tab[ix] = tab[i];
            tab[i] = min;
        }
}

void BubbleSort( int* tab, int nSize )
{
    for( int i = 0; i < nSize; i++ )
    {
        for( int j = nSize - 1; j > i; j-- )
        {
            if( tab[j] < tab[i] )
            {
            int temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}



void ShakeSort( int* tab, int nSize )
{
    int l = 1;
    int p = nSize - 1;
    int k = nSize - 1;
    
    do {
            for( int j = p; j >= l; j-- )
                if( tab[j - 1] > tab[j] ) //sortowanie babelkowe od prawej strony
                {
                    int x = tab[j - 1];
                    tab[j - 1] = tab[j];
                    tab[j] = x;
                    k = j;
                }
            l = k + 1; //ustawiam l tak, zeby nie porownywac znalezionego juz najmniejszego elementu
    
            for( int j = l; j <= p; j++ ) //sortowanie babelkowe od lewej strony
                if( tab[j - 1] > tab[j] )
                {
                    int x = tab[j - 1];
                    tab[j - 1] = tab[j];
                    tab[j] = x;
                    k = j;
                }
            p = k - 1; //ustawiam p tak, by nie porownywac znalezionego juz najwiekszego elementu
        } while( l <= p );
}


void HalfInsertionSort( int* tab, int nSize )
{
    
    for( int i = 1; i < nSize; i++ )
    {
        int x = tab[i];
        int l = 0;
        int p = i - 1;
        int m = 0;
        
        
        do{
            m = ( l + p )/2;
            if( x < tab[m] ) p = m - 1;
            else l = m + 1;
            }while( l <= p );
            
            for( int j = i - 1; j >= l; j-- )
            {
                tab[j+1] = tab[j];
            }
                
                tab[l] = x;
            
    }
}

void QuickSortInterface(int *tab, int size)
                        {
                            int l = 0;
                            int p = size-1;
                            QuickSort( tab, l, p );
                        }

void QuickSort( int* tab, int l , int p )
{
    int i = l; //ustawiam lewy licznik na skrajny lewy element tablicy
    int j = p; //to samo dla skrajnie prawego elementu
    int x = tab[(l + p) / 2]; //ustawiam pivot na srodek tablicy, ale jego wybor moze byc losowy

    do {
        while( tab[i] < x )
            i++; //jezeli element z lewej czesci tablicy jest mniejszy od piwota, przesuwam lewy licznik
        while( tab[j] > x )
            j--; //analogicznie dla prawego licznika
        if( i <= j ) //dokonujemy zamiany, jezeli elementy nie spelnily warunkow powyzszych petli
        {
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            i++;
            j--;
        }
    } while( i <= j ); //petla wykonuje sie do spotkania lub miniecia licznikow
    
    if( l < j )
        QuickSort( tab, l, j ); //sortuje lewa czesc tablicy
    if( i < p )
        QuickSort( tab, i, p ); //sortuje prawa czesc tablicy
}


void HeapSort( int* tab, int nSize )
{
    int l = ((nSize-1) / 2) + 1;
    int p = nSize-1;

    for( ; l>=0; l-- )
        Update( tab, l, p );
        
    for( ; p>0; p-- )
    {
        int x = tab[0];
        tab[0] = tab[p];
        tab[p] = x;
        Update( tab, 0, p-1 );
    }
    
}

void Update( int* tab, int l, int p )
{
    int i = l;
    int j = 2 * i + 1;
    int x = tab[i];

    while( j <= p )
    {
        if( j < p )
            if( tab[j] < tab[j + 1] )
                j++;
        if( x > tab[j] )
            break;
        
        tab[i] = tab[j];
        i = j;
        j = 2 * i + 1;
        
    }
    tab[i] = x;
}





void createTab( int tab[] )
{
    for( int i = 0; i < MAX; i++ )
    {
        tab[i] = rand()%6;
        cout << tab[i] << ' ';
    }
    cout << '\n';
}

void printTab( int tab[] )
{
for( int i = 0; i < 10; i++ )
   {
       cout << tab[i] << ' ';
   }
}
