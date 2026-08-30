/*
DAA LAB 5 - Question 3
Implement Quick Sort of N random elements stored in a file.

This template includes:
- Random-element generation
- File storage
- File reading
- Output of the sorted result

TODO:
Implement Quick Sort in quick_sort().
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int a[], int low, int high)
{
    /*
       TODO:
       Implement Quick Sort here.
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

    FILE *fp = fopen("quick_sort_input.txt", "w");
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

    fp = fopen("quick_sort_input.txt", "r");
    if (fp == NULL) {
        printf("Could not open input file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &a[i]);

    fclose(fp);

    quick_sort(a, 0, n - 1);

    fp = fopen("quick_sort_output.txt", "w");
    if (fp == NULL) {
        printf("Could not create output file.\n");
        free(a);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d\n", a[i]);

    fclose(fp);

    printf("Random elements stored in quick_sort_input.txt\n");
    printf("Sorted elements stored in quick_sort_output.txt\n");

    free(a);
    return 0;
}

/*
Complexity analysis:
State the best-case, average-case, and worst-case time complexity
of Quick Sort, and its auxiliary-space complexity.
*/
