#include<stdio.h>
#define c 5

void prInfo(int arr[])
{
    printf("%d\n", sizeof arr);
}

int main(void)
{
    int arr[]={1,2,3,4,5};
    char ss[][2]={"asd","asda"};
    printf("%d\n", sizeof arr);
    prInfo(arr);
    char *p = "abcd";
    char s[]="abcd";
    printf("%d %d %d\n", sizeof "abcd", sizeof p, sizeof s);

    int as[12]={0};
    int (*pas)[12]=&as;
    
    printf("%d ", pas[0][0]);
    typedef double D;
    
    const D* dd=NULL;

    return 0;
}