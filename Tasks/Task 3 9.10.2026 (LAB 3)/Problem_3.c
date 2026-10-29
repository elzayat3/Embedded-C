
#include <stdio.h>

#include <stdlib.h>

int count_duplicated(int*arr,int size);

void max_min_inarray(int*arr,int size,int*pmax,int*pmin);

int main()
{
    int arr[10]={1,1,3,3,3,3};
    int count=count_duplicated(arr,10);
    printf("the number of duplicated elements in the array is: %d\n",count);

}




int count_duplicated(int*arr,int size)
{

    int count=0,max=0,min=0;

    max_min_inarray(arr,size,&max,&min);

    int fsize=max-min+1;

    int*freq=(int*)calloc(fsize,sizeof(int));

    for(int i=0;i<size;i++)
    {
        freq[arr[i]-min]++;
    }


    for(int i=0;i<fsize;i++)
    {
        if(freq[i]>1)
        {
            count++;
        }
        else{;}
    }

    return count;
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