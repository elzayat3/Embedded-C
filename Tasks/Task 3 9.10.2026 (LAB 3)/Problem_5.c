

#include <stdlib.h>


#include "stdio.h"

void count_freq(int*arr,int size);

void max_min_inarray(int*arr,int size,int*pmax,int*pmin);

int main()
{
    int arr[20]={1,1,2,2,2,3,4,5,6,6,6};

    count_freq(arr,20);

}

void count_freq(int*arr,int size)
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
        printf("the number : %d  : the freq %d\n ",i+min,freq[i]);
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