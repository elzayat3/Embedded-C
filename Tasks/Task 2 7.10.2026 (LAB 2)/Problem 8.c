
#include<stdio.h>

#include <stdlib.h>

#include <time.h>


int main()
{
    int user_number=0;

    srand(time(NULL)); // to make rand start from diffrant point every time 
    
    int number=1+(rand()%100);  // generate a random number 

    printf("please guess the number : ");

    scanf("%d",&user_number);

    if(user_number==number)
    {
        printf("congrats your guess is right");

    }
    else
    {
        printf("unfortunately your guess is wrong \n");

        printf("the right number is %d",number);
    }

}