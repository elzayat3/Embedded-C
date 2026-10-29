#include <stdio.h>

int main()
{
    int num=0,i=0;

    printf("please enter a number: ");
    scanf("%d",&num);

    if(num <1 || num>100)
    {
        printf("invalid input please enter a number between 1 and 100\n");
    }
    else
    {
        for(i=1;i<=100;i++)
        {
            if(i%num==0)
            {
                printf("%d ",i);
            }
        }
        printf("\n");
    }

    return 0;
}