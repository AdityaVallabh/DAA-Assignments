
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int indices[1001]={0};

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 

    int L[n1], R[n2], Lindex[n1], Rindex[n2];;
 

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
		Lindex[i] = indices[l+i];
    }
        
    for (j = 0; j < n2; j++)
	{
        R[j] = arr[m + 1+ j];
		Rindex[j] = indices[m+1+j];
 	}

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
			indices[k] = Lindex[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
			indices[k] = Rindex[j];
            j++;
        }
        k++;
    }
 


    while (i < n1)
    {
        arr[k] = L[i];
		indices[k] = Lindex[i];
        i++;
        k++;
    }
 


    while (j < n2)
    {
        arr[k] = R[j];
		indices[k] = Rindex[j];
        j++;
        k++;
    }
}
 


void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {


        int m = l+(r-l)/2;
 

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 


void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%02d ", A[i]);
    printf("\n");

	for (i=0; i < size; i++)
        printf("%02d ", indices[i]);
    printf("\n");
}
 

int main()
{
    int arr[1001] = {0};
    int arr_size;

	printf("Enter the value of n: ");
	scanf("%d",&arr_size);
	
	srand(time(0));
    int i;
	for(i=0;i<arr_size;i++)
	{
		arr[i] = rand()%100;
		indices[i] = i;
	}
 
    printf("Given array is \n");
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    printf("\nSorted array is \n");
    printArray(arr, arr_size);

	
	int low = 0, high = arr_size-1, mid, index1=-1, index2=-1,key;
	printf("\nEnter search key: ");
	scanf("%d",&key);

    while(low < high) 
	{
        mid = (low + high) / 2;
        if(arr[mid] == key) 
		{
            index2 = mid;
			goto last;
        } 
		else if(arr[mid] < key) 
		{
            low = mid + 1;
        } 
		else if(arr[mid] > key) 
		{
            high = mid - 1;
        }
    }

    if(key == arr[low] || key == arr[high]) 
	{
        return (key == arr[low])? low : high;
    }
	else
	{
		index2 = -1;
	}

	last:
	{
    index1 = (index2 >= 0)? indices[index2] : -1;
    printf("\nOriginal Index: %d\n", index1);
    printf("New Index: %d\n", index2);
	}

    return 0;
}
