#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void b_sort(int arr[]); //bubble sort
void swap(int *a,int *b); //call by reference swap

int main()
{
    int arr[5];
    int i;
    srand(time(NULL)); // 매번 다른 랜덤 시드 생성

    for(i=0; i<5; i++)
    {
        arr[i] = rand()%100+1; // 1~100 사이의 랜덤값 생성
        printf("index[%d] : %d\n", i, arr[i]);
    }

    b_sort(arr); // arr를 bubble sort
    
    printf("after bubble sort\n");

    for(i=0; i<5; i++)
    {
        printf("index[%d] : %d\n", i, arr[i]);
    }

}

void b_sort(int arr[])
{
    int i,j;

    for(i=0; i<5; i++)
    {
        for(j=0; j<5-i; j++) // i=0:j=0~5, i=1:j=0~4... i=4:j=0
        {
            if(arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;

    *b = temp;
}