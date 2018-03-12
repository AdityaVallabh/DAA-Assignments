#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100
 
struct node 
{
	int data;
	struct node* next;
};
struct node *a;

void swap(struct node* i, struct node* j);

void updateLoc(struct node* head, int a);

void heapify(int n, int i);
 
void heapSort(int n);

void printArray(int n);

void trackingPositions(int n);

int main()
{
	int n,i;
	printf("Enter the size of array: ");
	scanf("%d",&n);

	srand(time(NULL));
	a = (struct node*) malloc(n * sizeof(struct node));
	for (i = 0; i < n;  i++) 
	{
		a[i].data = rand() % MOD;
		a[i].next = (struct node*)malloc(sizeof(struct node));

		a[i].next->data = i;
		a[i].next->next = NULL;
	}

	printf("\nBefore sorting:\n");
	printArray(n);
 
   	heapSort(n);
 
	printf("\nAfter sorting:\n");
   	printArray(n);
	printf("\nTracking positions:\n");
	trackingPositions(n);
	return 0;
}

void swap(struct node* i, struct node* j)
{
	int temp = i->data;
	i->data = j->data;
	j->data = temp;

	struct node* tempNode = i->next;
	i->next = j->next;
	j->next = tempNode;
}

void updateLoc(struct node* head, int a)
{
	struct node* temp = head;
	while (temp->next != NULL) 
	{
		temp = temp->next;
	}

	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	newNode->data = a;
	newNode->next = NULL;

	temp->next = newNode;
}

void heapify(int n, int i)
{
    int largest = i;  
    int left = 2*i + 1;  
    int right = 2*i + 2;  
 
    if (left < n && a[left].data > a[largest].data)
        largest = left;
 
    if (right < n && a[right].data > a[largest].data)
        largest = right;
 
    if (largest != i)
    {
        swap(&a[i], &a[largest]);
 	updateLoc(a + i, i);
	updateLoc(a + largest, largest);
        heapify(n, largest);
    }
}
 
void heapSort(int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);
 
    for (int i=n-1; i>=0; i--)
    {
        swap(&a[0], &a[i]);
 		updateLoc(a, 0);
		updateLoc(a + i, i);
        heapify(i, 0);
    }
}
 

void printArray(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
	printf("%02d ",a[i].data);
	}
	printf("\n");
}

void trackingPositions(int n)
{
	int i;
	for(i=0;i<n;i++) 
	{
		printf("%02d: ", a[i].data);
		
		struct node* temp = a[i].next;
		while (temp != NULL) 
		{
			printf("%02d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}
