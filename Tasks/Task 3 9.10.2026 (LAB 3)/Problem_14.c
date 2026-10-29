#include <stdio.h> 


void string_capital(char*str);

void string_scan(char *str,int maxSize);


int main()
{
    char str[100];
    printf("please enter a string : ");
    string_scan(str,100); 
    string_capital(str);
    printf("the string after capital is : %s",str);
   
}



void string_capital(char*str)
{
	int i;
	for(i=0;str[i];i++)
	{
		if((str[i]>='a')&&(str[i]<='z'))
		{
			str[i]=(str[i]-'a')+'A';
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




