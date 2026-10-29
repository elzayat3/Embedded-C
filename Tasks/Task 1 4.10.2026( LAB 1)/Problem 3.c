#include <stdio.h>

int main()
{
    int num1=0,num2=0;

    printf("please enter two integers: ");
    scanf("%d %d",&num1,&num2);

    if (num1%num2==0 || num2%num1==0)
    {
        printf("The numbers are multiples of each other\n");
    }
    else
    {
        printf("The numbers are not multiples of each other\n");
    }

    return 0;
}