
#include <stdio.h>

void reverse_array(int*arr,int size);

void swap(int*x,int*y);

void array_printint(int*arr,int size);

int main()
{

	int arr[10]={1,2,3,4,5,6,7,8,9,10};

	array_printint(arr,10);
	reverse_array(arr,10);
	array_printint(arr,10);

    

}


void reverse_array(int*arr,int size)
{
	int i,j;
	for(i=0,j=size-1;i<(size/2);i++,j--)
	{
		swap(&arr[i],&arr[j]);
	}
}


void swap(int*x,int*y)
{

    int temp=*(x);

    *(x)=*(y);

    *(y)=temp;

}

void array_printint(int*arr,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
}