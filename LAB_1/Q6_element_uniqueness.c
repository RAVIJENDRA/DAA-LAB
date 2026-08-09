#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i, j;
    int duplicate = 0;
    long long comparisons = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int a[n];

    srand(time(NULL));

    printf("\nRandom numbers:\n");

    for(i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        printf("%d ", a[i]);
    }

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            comparisons++;

            if(a[i] == a[j])
            {
                duplicate = 1;
                break;
            }
        }

        if(duplicate)
            break;
    }

    printf("\n\n");

    if(duplicate)
        printf("Duplicate element found.\n");
    else
        printf("All elements are unique.\n");

    printf("Number of comparisons = %lld\n", comparisons);

    return 0;
}
