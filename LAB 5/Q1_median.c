/*
DAA LAB 5 - Question 1
Find the median of a list of N numbers without sorting the list.

Requirement:
- The input list must NOT be sorted as part of the solution.
- Complexity analysis is required.

TODO:
Implement a selection-based median algorithm here.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;

    printf("Enter number of elements: ");
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

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    /*
       TODO:
       Find the median WITHOUT sorting a[].

       For odd n:
           median = element with rank (n + 1) / 2

       For even n:
           median = average of the elements with ranks n/2 and n/2 + 1

       Use a selection algorithm rather than a sorting algorithm.
    */

    printf("\nMedian calculation is the algorithm section to complete.\n");

    free(a);
    return 0;
}

/*
Complexity analysis:
Write the time and auxiliary-space complexity of the selection
algorithm used above.
*/
