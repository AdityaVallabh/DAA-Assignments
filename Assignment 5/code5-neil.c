#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MOD 100

int i = 0;  // counter for input traversal

int* generate_arr(int n)
{
	srand(time(NULL));

	int* arr = (int*) malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % MOD;
	}

	return arr;
}

void printArray(int *arr, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        printf("%02d ", arr[i]);
    }
    printf("\n");
}

void build_tree(int* tree_arr, int n, int node, int* traversal_arr)
{
	if (node < n) {
		build_tree(tree_arr, n, 2 * node + 1, traversal_arr);
		tree_arr[node] = traversal_arr[i];
		i++;
		build_tree(tree_arr, n, 2 * node + 2, traversal_arr);
	}
}

void traverse_inorder(int* tree, int n, int node)
{
	if (node < n) {
		traverse_inorder(tree, n, 2 * node + 1);
		printf("%02d ", tree[node]);
		traverse_inorder(tree, n, 2 * node + 2);
	}
}

int main()
{
	char* yellow = "\033[33m";
	char* green = "\033[32m";
	char* white = "\033[37m";
	char* black = "\033[30m";

	int n;
	printf("%sEnter the number of elements in the in-order traversal: %s", white, black);
	scanf("%d", &n);

	// make random traversal arr
	int* traversal = generate_arr(n);
	printf("%sInput traversal:\n%s", yellow, black);
	printArray(traversal, n);

	// make empty tree arr
	int* tree = (int*) malloc(n * sizeof(int));

	// build tree from the traversal
	build_tree(tree, n, 0, traversal);
	printf("%sBuilt tree:\n%s", green, black);
	printArray(tree, n);

	// verify
	printf("%sComparison:\n%s", white, black);
	printf("%sInput traversal:\t%s", yellow, black);
	printArray(traversal, n);
	printf("%sBuilt tree traversal:\t%s", green, black);
	traverse_inorder(tree, n, 0);
	printf("\n");

	return 0;
}
