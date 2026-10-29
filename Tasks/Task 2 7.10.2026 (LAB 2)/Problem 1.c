
#include<stdio.h>

int main()
{
    int first=0,last=0,flag=0;

    printf("please enter the first number :");

    if(scanf("%d",&first) != 1)
    {
        printf("invalid input");
        flag=1;
    }
    else{;}

    if(flag==0)
    {
        printf("please enter the last number :");

        if(scanf("%d",&last) != 1)
        {
            
            printf("invalid input");
            flag=1;
        }
        else{;}
    }
    else{;}

    if(flag==0)
    {
        if(first==last || (first+1)==last || first==(last+1))
        {
            printf("there are no numbers between them");
        }
        else
        {
            printf("the even numbers are : ");

            for(int i=first;i<=last;i++)
            {
                if(i%2==0)
                {
                    printf("%d ",i);
                }
                else{;}
            }
            printf("\n");
            printf("the odd numbers are : ");

            for(int i=first;i<=last;i++)
            {
                if(i%2!=0)
                {
                    printf("%d ",i);
                }
                else{;}
            }
        }
    }

    
    

    printf("\n");


}