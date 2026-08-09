#include <stdio.h>

int main()
{
    int n, i;
    int low, high, mid;
    int position = -1;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int a[n];

    printf("Enter the elements (0s followed by 1s):\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);

        if(a[i] != 0 && a[i] != 1)
        {
            printf("Only 0 and 1 are allowed.\n");
            return 1;
        }
    }

    low = 0;
    high = n - 1;

    /* Binary search for the first 1 */
    while(low <= high)
    {
        mid = low + (high - low) / 2;

        if(a[mid] == 1)
        {
            position = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if(position == -1)
    {
        printf("No transition found because the array contains only 0s.\n");
    }
    else if(position == 0)
    {
        printf("Transition point is before position 0.\n");
        printf("The array starts with 1.\n");
    }
    else
    {
        printf("Last 0 is at position %d\n", position - 1);
        printf("First 1 is at position %d\n", position);
        printf("Transition is between positions %d and %d.\n",
               position - 1, position);
    }

    return 0;
}
