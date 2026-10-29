
#include<stdio.h>

int main()
{
    int rows=0;

    printf("please enter the number of rows : ");


    if(scanf("%d",&rows)==1)
    {
        if(rows>0)
        {
            for(int i=1;i<=rows;i++)
            {
                for(int j=0;j<i;j++)
                {
                    printf("*");
                }
                printf("\n");
            }

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

}