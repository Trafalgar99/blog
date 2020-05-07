#include <stdio.h>
#define MSG "I　am　a　symbolic　string　constant"
#define MAXLENGTH 81

int main()
{
    char *p1 = "Klingon";
    
    printf("Kligon");
    printf(": Beware the %ss!\n", "Klingon");

    gets_s(p1,5);
    fgets(p1, 5, stdin);

    return 0;
}