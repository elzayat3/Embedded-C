
#include <stdio.h>

void array_printint(int*arr,int size);

void copy_array(int*arr1,int*arr2,int size1,int size2);

int main()
{

    int arr1[10]={1,2,3,4,5,6,7,8,9,10};
    int arr2[5]={0};
    printf("Array 1 before copy:\n");
    array_printint(arr1,10);
    printf("Array 2 before copy:\n");
    array_printint(arr2,5);
    copy_array(arr1,arr2,10,5);
    printf("Array 2 after copy:\n");
    array_printint(arr2,5);

    
}


void copy_array(int*arr1,int*arr2,int size1,int size2)
{
    int i;
    if(size1>size2)
    {
        for(i=0;i<size2;i++)
        {
            arr2[i]=arr1[i];
        }
    }
    else
    {
        for(i=0;i<size1;i++)
        {
            arr2[i]=arr1[i];
        }
    }
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