#include "function.h"
uint8 Limit_uint8( uint8 a, uint8 b, uint8 c )
{
    if( ( b >= a ) && ( b <= c ) )
    {
        return b;
    }
    else if( b < a )
    {
        return a;
    }
    else if( b > c )
    {
        return c;
    }
    return 0;
}
