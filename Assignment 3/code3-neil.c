#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MOD 100

struct Node {
	int data;
	struct Node* next;
};

struct Node* generateArray(int n)
{
	int seed = time(NULL);
	srand(seed);

	struct Node* arr = (struct Node*) malloc(n * sizeof(struct Node));
	for (int i = 0; i < n; i++) {
		arr[i].data = rand() % MOD;
		arr[i].next = (struct Node*) malloc(sizeof(struct Node));

		arr[i].next->data = i;
		arr[i].next->next = NULL;
	}

	return arr;
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

int findSmallest(struct Node* arr, int l, int r)
{
	int sInd = l, small = arr[l].data;
	for (int i = l+1; i <= r; i++) {
		if (arr[i].data < small) {
			sInd = i;
			small = arr[sInd].data;
		}
	}

	return sInd;
}

int findLargest(struct Node* arr, int l, int r)
{
	int lInd = l, large = arr[l].data;
	for (int i = l+1; i <= r; i++) {
		if (arr[i].data >= large) {
			lInd = i;
			large = arr[lInd].data;
		}
	}

	return lInd;
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

void sort(struct Node* arr, int n)
{
	int l = 0, r = n - 1;
	while (l < r) {
		int sInd = findSmallest(arr, l, r);
		if (l != sInd) {
			swap(arr + l, arr + sInd);
			updateLoc(arr + l, l);
			updateLoc(arr + sInd, sInd);
		}

		int lInd = findLargest(arr, l, r);
		if (r != lInd) {
			swap(arr + r, arr + lInd);
			updateLoc(arr + r, r);
			updateLoc(arr + lInd, lInd);
		}

		l++;
		r--;
	}
}


int main()
{
	int n;
	printf("Enter n: ");
	scanf("%d", &n);
	struct Node* arr = generateArray(n);
	printArray(arr, n);
	sort(arr, n);
	printWithTracks(arr, n);

	return 0;
}
