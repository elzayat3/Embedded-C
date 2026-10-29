
#include<stdio.h>

int main()
{
    int total_seconds=0;

    printf("please enter the number of seconds ");

    scanf("%d",&total_seconds);

    if(total_seconds<0)
    {
        printf("wrong input");
    }
    else
    {
          int hours=total_seconds/3600;
          int minutes=(total_seconds%3600)/60;
          int seconds=total_seconds%60;

          printf("Time: %d hours, %d minutes, %d seconds\n",hours,minutes,seconds);
    }

  

    return 0;
}