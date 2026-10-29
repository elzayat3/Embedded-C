#include "stdio.h"

void string_scan(char *str,int maxSize);

int str_length(char*str);


int main()
{
    printf("please enter a string : ");
    char str[100];
    string_scan(str,100);
    printf("the length of the string is : %d",str_length(str));
   
}


int str_length(char*str)
{
	int i;
	for(i=0;str[i];i++)
	{;}
	return i;
		//count without null number of char
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