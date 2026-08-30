/*
DAA LAB 5 - Question 4
Implement Heap Sort to sort N randomly generated elements
stored in a file.

Requirement:
- Randomly generated elements are stored in a file.
- Implement Heap Sort.
- Do the complexity analysis.

TODO:
Implement heapify() and heap_sort().
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int a[], int n, int i)
{
    /*
       TODO:
       Maintain the max-heap property for the subtree rooted at i.
    */
}

void heap_sort(int a[], int n)
{
    /*
       TODO:
       1. Build a max heap.
       2. Repeatedly move the maximum element to the end.
       3. Restore the heap property.
    */
}

int main(void)
{
    int n;

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("N must be positive.\n");
        return 1;
    }

    int *a = malloc((size_t)n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand((unsigned)time(NULL));

    FILE *fp = fopen("heap_sort_input.txt", "w");
    if (fp == NULL) {
        printf("Could not create input file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100000;
        fprintf(fp, "%d\n", a[i]);
    }

    fclose(fp);

    fp = fopen("heap_sort_input.txt", "r");
    if (fp == NULL) {
        printf("Could not open input file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    heap_sort(a, n);

    fp = fopen("heap_sort_output.txt", "w");
    if (fp == NULL) {
        printf("Could not create output file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", a[i]);

    fclose(fp);

    printf("Random elements stored in heap_sort_input.txt\n");
    printf("Sorted elements stored in heap_sort_output.txt\n");

    free(a);
    return 0;
}

/*
Complexity analysis:
State the time complexity of building the heap, the repeated
heap-sort phase, overall Heap Sort, and auxiliary-space complexity.
*/
