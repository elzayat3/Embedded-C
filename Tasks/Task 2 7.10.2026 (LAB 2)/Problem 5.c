

#include<stdio.h>


int main()
{
    int number=0,prime=1;

    printf("please enter the number : ");

    if(scanf("%d",&number)==1)
    {
        if(number >=0)
        {
            if(number<2)
            {
                prime=0;
            }
            else
            {
                for(int i=2;(i<number)&&(1==prime);i++)
                {
                    if(number%i==0)
                    {
                        prime=0;
                    }
                    else{;}
                }
            }

            if(0==prime)
            {
                printf("not prime number");
            }
            else
            {
                printf("prime number");
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