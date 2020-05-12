#include<stdio.h>

union test
{
    /* data */
    int i;
    char c;
};


int main(void)
{   
    union test t;
    t.c='A';
    printf("%c %c", t.i, t.c);
    return 0;
}