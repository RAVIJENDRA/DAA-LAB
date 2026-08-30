/*
DAA LAB 5 - Question 2
Find the K'th smallest element in a given list of N numbers
without sorting the list.

Requirement:
- The list must NOT be sorted as part of the solution.
- Complexity analysis is required.

TODO:
Implement a selection-based K'th-smallest algorithm.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("N must be positive.\n");
        return 1;
    }

    printf("Enter K (1 to %d): ", n);
    scanf("%d", &k);

    if (k < 1 || k > n) {
        printf("Invalid K.\n");
        return 1;
    }

    int *a = malloc((size_t)n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    /*
       TODO:
       Find the K'th smallest element WITHOUT sorting a[].

       K = 1  -> smallest element
       K = N  -> largest element

       Use a selection algorithm rather than a sorting algorithm.
    */

    printf("\nK'th-smallest calculation is the algorithm section to complete.\n");

    free(a);
    return 0;
}

/*
Complexity analysis:
Write the time and auxiliary-space complexity of the selection
algorithm used above.
*/
