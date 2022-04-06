#include "onpfun.h"
#include <stdio.h>
#include <iostream>
#include "Stack.h"
#include <math.h>
#include <float.h>
#include "DStack.h"
using namespace std;

#define DOT '.'

double GetNum();
void skipSpaces();
int isOper( char cOper );
int prior( char cOper );
int isDigit( char cOper );
double Eval( char cOper, double argl, double arg2 ); //do kalkulatora


//---------------------------------------------------------------------
double GetNum()
{
    char   c;
    double res = 0;
    int    sign = 0;

    skipSpaces();

    if( ( c = getchar() ) == '-' ) sign = 1;  // pomijanie znakow
    else if( c != '+' ) ungetc(c, stdin);

    while( isDigit(c = getchar() ) ) //horner czesc rzeczywista
        res = res * 10 + ( c - '0' );

    if( c == DOT )
    {
        double coef = 0.1;
        while( isDigit( c = getchar() ) )    // czesc ulamkowa
        {
            res += ( c - '0' ) * coef;
            coef *= 0.1;
        }
    }
    ungetc( c, stdin );

    if( sign ) res = -res;
    return res;
}


//---------------------------------------------------------------------
void skipSpaces()
{
    char c;
    while( ( c = getchar() ) == ' ' );  // mozna uzyc funkcji isspace
    ungetc( c, stdin );
}


//---------------------------------------------------------------------
char getOper()
{
    skipSpaces();
    return getchar();
}


//---------------------------------------------------------------------
int isOper( char c )
{
    switch( c )
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^': return 1;
    }
    return 0;
}


//---------------------------------------------------------------------
int prior( char cOper )
{
    switch( cOper )
    {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    }
    return 0;
}


//---------------------------------------------------------------------
int isDigit( char c )
{
    return ( c >= '0' ) && ( c <= '9' );
}


//---------------------------------------------------------------------
double Eval( char cOper, double arg1, double arg2 )   // do kalkulatora
{
    switch( cOper )
    {
    case '+': return arg1 + arg2;
    case '-': return arg1 - arg2;
    case '*': return arg1 * arg2;
    case '/':  if( fabs(arg2) > 1e-15 )  // dzielenie przez 0
        return arg1 / arg2;
        perror( "ERROR : Devisin by 0\n" );
        return DBL_MIN;
    case '^': return pow( arg1, arg2 );   // wyjatkowo uzywamy  pow normalnie zabronione
    }
    return 0;

}


//---------------------------------------------------------------------
double calc()
{

    StackItem* pStack;
    initStack( &pStack );
    DStackItem* pDStack;
    initDStack( &pDStack );


    char c;

    dpush( GetNum(), &pDStack ); //wczytuje i wklada na stos liczbowy pierwsza liczbe

    while( isOper(c = getchar() ) ) //petla dziala dopoki wczytujemy operator
    {
        while( prior( c ) <= prior( top( pStack ) ) )
        {
            double arg2 = dpop( &pDStack );
            dpush( Eval( pop( &pStack ), dpop( &pDStack ), arg2 ), &pDStack );
        }
        push( c, &pStack );
        dpush( GetNum(), &pDStack ); //wczytana kolejna liczba trafia na stos liczbowy
    }
    while( !isEmpty( pStack ) ) //dopoki niepusty stos z operatorami to obliczamy
    {
        double arg2 = dpop( &pDStack );
        dpush( Eval( pop( &pStack ), dpop( &pDStack ), arg2 ), &pDStack );
    }


    return dpop( &pDStack );
}
