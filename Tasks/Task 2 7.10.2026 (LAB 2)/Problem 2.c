#include<stdio.h>

int main()
{
    int number =0,res=1;

    printf("please enter the number : ");

    if(scanf("%d",&number) == 1)
    {
        if(number >=0)
        {
            for(int i=number;i>=2;i--)
            {
                res=res*i;
            }

            printf("the factorial of %d is %d ",number,res);
        }
        else
        {
            printf("wrong number");
        }
    }
    else
    {
        printf("invalid input");
    }

    
    printf("\n");
}