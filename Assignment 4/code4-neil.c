#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

struct Node {
	int data;
	struct Node* next;
};

struct Node* generate_arr(int n)
{
	srand(time(NULL));

	struct Node* arr = (struct Node*) malloc(n * sizeof(struct Node));
	for (int i = 0; i < n;  i++) {
		arr[i].data = rand() % MOD;
		arr[i].next = (struct Node*) malloc(sizeof(struct Node));

		arr[i].next->data = i;
		arr[i].next->next = NULL;
	}

	return arr;
}

void swap(struct Node* i, struct Node* j)
{
	int tmpData = i->data;
	struct Node* tmpNext = i->next;

	i->data = j->data;
	i->next = j->next;
	j->data = tmpData;
	j->next = tmpNext;
}

void updateLoc(struct Node* head, int a)
{
	struct Node* i = head;
	while (i->next != NULL) {
		i = i->next;
	}

	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	newNode->data = a;
	newNode->next = NULL;

	i->next = newNode;
}

void printArray(struct Node* arr, int n)
{
	printf("Array: ");
	for (int i = 0; i < n; i++) {
		printf("%02d ", arr[i].data);
	}
	printf("\n");
}

void printList(struct Node* head)
{
	struct Node* i = head;
	while (i != NULL) {
		printf("%02d ", i->data);
		i = i->next;
	}
	printf("\n");
}

void printWithTracks(struct Node* arr, int n)
{
	printf("Array:\n");
	for (int i = 0; i < n; i++) {
		printf("%02d: ", arr[i].data);
		printList(arr[i].next);
	}
}

void max_heapify(struct Node* arr, int n, int root)
{
	int largest = root;
	int left = 2 * root + 1;
	int right = left + 1;

	if (left < n && arr[left].data > arr[largest].data) {
		largest = left;
	}
	if (right < n && arr[right].data > arr[largest].data) {
		largest = right;
	}

	if (largest != root) {
		swap(arr + root, arr + largest);
		updateLoc(arr + root, root);
		updateLoc(arr + largest, largest);
		max_heapify(arr, n, largest);
	}
}

void build_maxheap(struct Node* arr, int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--) {
		max_heapify(arr, n, i);
	}
}

void heapsort(struct Node* arr, int n)
{
	build_maxheap(arr, n);
	for (int i = n - 1; i > 0; i--) {
		swap(arr, arr + i);
		updateLoc(arr, 0);
		updateLoc(arr + i, i);
		max_heapify(arr, i, 0);
	}
}

int main()
{
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	struct Node* arr = generate_arr(n);
	printArray(arr, n);
	heapsort(arr, n);
	printWithTracks(arr, n);

	return 0;
}
