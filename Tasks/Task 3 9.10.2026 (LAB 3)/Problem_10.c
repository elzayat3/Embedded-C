#include "stdio.h"


int count_words(char*str);
void string_scan(char *str,int maxSize);


int main()
{

    printf("please enter a string : ");
    char str[100];
    string_scan(str,100);
    int count=count_words(str);
    printf("the number of words in the string is : %d",count);

}


int count_words(char*str)
{
    int i=0,count=0;
    while(str[i])
    {
        if((str[i]==' ')&&(str[i+1]!=' '))
        {
            count++;
        }
        i++;
    }
    return count+1;
}


void string_scan(char *str,int maxSize)
{
    int i=0;
    fflush(stdin);
    scanf("%c",&str[i]);
    while((str[i]!='\n')&&(i<maxSize-1))
    {
        i++;
        scanf("%c",&str[i]);
    }
    str[i]=0;
}