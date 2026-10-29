

#include <stdlib.h>


#include "stdio.h"

void max_min_inarray(int*arr,int size,int*pmax,int*pmin);

void print_uniq(int*arr,int size);
int main()
{
    int arr[10]={1,2,3,0};

    print_uniq(arr,10);

}


void print_uniq(int*arr,int size)
{
    int max=0,min=0;

    max_min_inarray(arr,size,&max,&min);

    int fsize=max-min+1;

    int*freq=(int*)calloc(fsize,sizeof(int));

    for(int i=0;i<size;i++)
    {
        freq[arr[i]-min]++;
    }


    for(int i=0;i<fsize;i++)
    {
        if(freq[i]==1)
        {
            printf("%d ",i+min);
        }
    }

}
void max_min_inarray(int*arr,int size,int*pmax,int*pmin)
{
	int i,max,min;
	for(i=0;i<size;i++)
	{
		if(0==i)
		{
			max=arr[i];
			min=arr[i];
		}
		else
		{
			if(arr[i]>max)
			{
				max=arr[i];
			}
			else{;}
			if(arr[i]<min)
			{
				min=arr[i];
			}
			else {;}
		}
	}
	*(pmax)=max;
	*(pmin)=min;
}






