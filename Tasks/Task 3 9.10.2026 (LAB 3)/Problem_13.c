#include <stdio.h>


int str_length(char*str);

void string_copy(char*s,char*s1);

void string_scan(char *str,int maxSize);


int main()
{
    char str[100],str1[100];
    printf("please enter the string : ");
    string_scan(str1,100);
    string_copy(str,str1);
    printf("the string after copy is : %s",str);
}





void string_copy(char*s,char*s1)
{

    int i;
    int size1=str_length(s);
    int size2=str_length(s1);

    if(size1>=size2)
    {
        for(i=0;s1[i];i++)
        {
            s[i]=s1[i];
        }
        s[i]=0;
    }
    else
    {
        printf("wrong input"); 
    }
    
    
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