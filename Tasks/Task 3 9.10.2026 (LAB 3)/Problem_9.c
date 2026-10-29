
#include "stdio.h"

void binary_print(unsigned int n);

int main()
{
    while(1)
    {
        unsigned int n=0;
        printf("please enter a number : ");
        fflush(stdin);

        scanf("%d",&n);
        binary_print(n);
    }
   
}

void binary_print(unsigned int n)
{
	int i,flag=0;;
	for(i=((sizeof(n)*8)-1);i>=0;i--)
	{
		
		if((n>>i)&1)//read bit
		{
			printf("1");
			flag=1;
		}
		else
		{
			if(1==flag)
			{
				printf("0");
			}
		}
	}	
}