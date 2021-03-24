#include <stdio.h>
#include <time.h>

void insert_sort(int arr[], int n); // 배열, 배열길이 

int main()
{
	int arr[10] = {13,3,7,8,47,6,8,4,36,27};
	
	clock_t start, stop;
	
	start = clock();
	int i;
	for(i=0; i<1000000; i++)
	{
		insert_sort(arr, 10);
	}
	
	stop = clock();
	
	double runtime = (double)(stop - start);
	
	printf("Sort time : %f", runtime);
}

void insert_sort(int arr[], int n) //삽입 정렬 
{
	int i,j;
	
	for(i=0; i<n; i++)
	{
		int temp = arr[i];
		for(j=i-1; j>=0 && temp < arr[j]; j--)
		{
			arr[j+1] = arr[j];
			arr[j] = temp;
		}
	}
}
