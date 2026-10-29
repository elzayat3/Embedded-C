
#include "stdio.h"
char str_compare(char*str1,char*str2);

void string_small(char*str);

void string_scan(char *str,int maxSize);
int main()
{
    char str1[100],str2[100];
    printf("please enter the first string : ");
    string_scan(str1,100);
    printf("please enter the second string : ");
    string_scan(str2,100);
    if(1==str_compare(str1,str2))
    {
        printf("the two strings are equal");
    }
    else
    {
        printf("the two strings are not equal");
    }
}



char str_compare(char*str1,char*str2)
{
	int i,c;
	c=1;
	string_small(str1);
	string_small(str2);
	for(i=0;(str1[i]||str2[i]);i++)
	{
		if(str1[i]==str2[i])
		{
			;
		}
		else
		{
			c=0;
		}
	}
	return c;// 1 if equal 0 if not
}

void string_small(char*str)
{
	int i;
	for(i=0;str[i];i++)
	{
		if((str[i]>='A')&&(str[i]<='Z'))
		{
			str[i]=(str[i]-'A')+'a';
		}
		else{;}
	}
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