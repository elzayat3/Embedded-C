#include "stdio.h"

void sort_arr_asc(int*arr,int size);

void swap(int*x,int*y);

void array_printint(int*arr,int size);

int main()
{
    int arr[20]={1,1,2,2,2,3,-4,5,45,6,6};
    array_printint(arr,20);
    sort_arr_asc(arr,20);
    array_printint(arr,20);
}


void sort_arr_asc(int*arr,int size)
{
    int i,j,f=0;
    for(i=0;(i<size)&&(0==f);i++)
    {
        f=1;
        for(j=0;j<size-1-i;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                f=0;
            }
            else{;}
        }
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