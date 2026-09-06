#include <stdio.h>

/* Reverse elements from index l to r */
void reverse(int a[], int l, int r)
{
    int temp;

    while (l < r)
    {
        temp = a[l];
        a[l] = a[r];
        a[r] = temp;

        l++;
        r--;
    }
}

/*
    Stable partition the array from l to r.

    Elements <= value are placed first.
    Elements > value are placed second.

    Returns the number of elements <= value.
*/
int stablePartition(int a[], int l, int r, int value)
{
    int mid;
    int leftCount, rightCount;
    int leftLength;
    int falseLeft;
    int trueRight;

    if (l == r)
    {
        if (a[l] <= value)
            return 1;
        else
            return 0;
    }

    mid = (l + r) / 2;

    /* Partition left half */
    leftCount = stablePartition(a, l, mid, value);

    /* Partition right half */
    rightCount = stablePartition(a, mid + 1, r, value);

    leftLength = mid - l + 1;

    /*
        After partition:

        Left half:
        [elements <= value][elements > value]

        Right half:
        [elements <= value][elements > value]

        We need to exchange:

        [elements > value] [elements <= value]
    */

    falseLeft = leftLength - leftCount;
    trueRight = rightCount;

    /*
        First reverse the elements > value
        in the left half.
    */
    if (falseLeft > 0)
    {
        reverse(a, l + leftCount, mid);
    }

    /*
        Then reverse the elements <= value
        in the right half.
    */
    if (trueRight > 0)
    {
        reverse(a, mid + 1, mid + trueRight);
    }

    /*
        Finally reverse both blocks together.
        This exchanges their positions.
    */
    if (falseLeft > 0 && trueRight > 0)
    {
        reverse(a, l + leftCount, mid + trueRight);
    }

    return leftCount + rightCount;
}

/*
    Sort the values from low to high.
*/
void sortRange(int a[], int l, int r, int low, int high)
{
    int mid;

    if (low >= high)
        return;

    mid = (low + high) / 2;

    /*
        Put values low...mid first
        and values mid+1...high second.
    */
    stablePartition(a, l, r, mid);

    /*
        Number of values in the lower half.
    */
    int lowerCount = mid - low + 1;

    /*
        Recursively sort lower half.
    */
    sortRange(a, l, l + lowerCount - 1, low, mid);

    /*
        Recursively sort upper half.
    */
    sortRange(a, l + lowerCount, r, mid + 1, high);
}

int main()
{
    int n;
    int a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the permutation: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    sortRange(a, 0, n - 1, 1, n);

    printf("Sorted permutation: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}