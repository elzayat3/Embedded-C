

#include "stdio.h"


void max_min_inarray(int*arr,int size,int*pmax,int*pmin);


int main()
{
    int max,min;
    int arr[20]={1,1,2,2,2,3,-4,5,45,6,6};

    max_min_inarray(arr,20,&max,&min);


    printf("the max is : %d  the min is : %d",max,min);

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