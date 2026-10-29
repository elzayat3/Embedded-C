
#include <stdio.h>

int main()
{
    int month=0;

    printf(" please enter month number from 1 to 12: ");
    scanf("%d", &month);

    if(month<1 || month>12)
    {
        printf("invalid month number please enter a number between 1 and 12\n");
    }
    else
    {
        switch(month)
        {
            case 1:
                printf("January\n");
                break;
            case 2:
                printf("February\n");
                break;
            case 3:
                printf("March\n");
                break;
            case 4:
                printf("April\n");
                break;
            case 5:
                printf("May\n");
                break;
            case 6:
                printf("June\n");
                break;
            case 7:
                printf("July\n");
                break;
            case 8:
                printf("August\n");
                break;
            case 9:
                printf("September\n");
                break;
            case 10:
                printf("October\n");
                break;
            case 11:
                printf("November\n");
                break;
            case 12:
                printf("December\n");
                break;
        }
    }  

    return 0;
}