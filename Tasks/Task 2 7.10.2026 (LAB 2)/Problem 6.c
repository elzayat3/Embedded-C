
#include<stdio.h>

int main()
{
    int year=0;
    printf("please enter the year : ");

    if(scanf("%d",&year)==1)
    {
        if(year >=0)
        {
            if((year%400==0) ||((year%4==0) &&(year%100!=0)))
            {
                printf("it is a leap year");
            }
            else
            {
                printf("is is not leap year");
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