#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX 100

/* Function to find maximum element */
int findMaximum(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

/* Function to find first and second largest distinct elements */
void findLargestTwo(int arr[], int n, int *largest, int *secondLargest)
{
    *largest = arr[0];
    *secondLargest = INT_MIN;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *largest)
        {
            *secondLargest = *largest;
            *largest = arr[i];
        }
        else if (arr[i] > *secondLargest && arr[i] != *largest)
        {
            *secondLargest = arr[i];
        }
    }
}

/* Function to find mean */
double findMean(int arr[], int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum = sum + arr[i];
    }

    return (double)sum / n;
}

/* Merge two sorted parts */
void merge(int arr[], int left, int mid, int right)
{
    int temp[MAX];
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

/* Merge Sort */
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Function to find median */
double findMedian(int arr[], int n)
{
    int temp[MAX];

    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }

    mergeSort(temp, 0, n - 1);

    if (n % 2 == 1)
    {
        return temp[n / 2];
    }
    else
    {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
}

/* Function to find standard deviation */
double findStandardDeviation(int arr[], int n)
{
    double mean = findMean(arr, n);
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double difference = arr[i] - mean;
        sum = sum + difference * difference;
    }

    return sqrt(sum / n);
}

/* Function to find mode */
int findMode(int arr[], int n)
{
    int mode = arr[0];
    int maxFrequency = 1;

    for (int i = 0; i < n; i++)
    {
        int frequency = 0;

        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                frequency++;
            }
        }

        if (frequency > maxFrequency)
        {
            maxFrequency = frequency;
            mode = arr[i];
        }
    }

    return mode;
}

/* Function to remove duplicates */
int removeDuplicates(int arr[], int n)
{
    int unique[MAX];
    int uniqueCount = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < uniqueCount; j++)
        {
            if (arr[i] == unique[j])
            {
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            unique[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    for (int i = 0; i < uniqueCount; i++)
    {
        arr[i] = unique[i];
    }

    return uniqueCount;
}

/* Function to reverse the array */
void reverseArray(int arr[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }
}

/* Function to partition array around pivot */
void partitionArray(int arr[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        while (left < right && arr[left] >= pivot)
        {
            left++;
        }

        while (left < right && arr[right] < pivot)
        {
            right--;
        }

        if (left < right)
        {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;

            left++;
            right--;
        }
    }
}

/* Function to print array */
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

/* Main function */
int main()
{
    int arr[MAX];
    int n;
    int pivot;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nOriginal Array: ");
    printArray(arr, n);

    /* 1. Maximum */
    printf("\n1. Maximum element = %d\n", findMaximum(arr, n));

    /* 2. First and second largest */
    int largest, secondLargest;

    findLargestTwo(arr, n, &largest, &secondLargest);

    printf("2. First largest = %d\n", largest);

    if (secondLargest == INT_MIN)
    {
        printf("   Second largest distinct element does not exist.\n");
    }
    else
    {
        printf("   Second largest = %d\n", secondLargest);
    }

    /* 3. Mean */
    printf("\n3. Mean = %.2f\n", findMean(arr, n));

    /* 4. Median */
    printf("4. Median = %.2f\n", findMedian(arr, n));

    /* 5. Standard deviation */
    printf("5. Standard deviation = %.2f\n",
           findStandardDeviation(arr, n));

    /* 6. Mode */
    printf("6. Mode = %d\n", findMode(arr, n));

    /* 7. Remove duplicates */
    int duplicateArray[MAX];

    for (int i = 0; i < n; i++)
    {
        duplicateArray[i] = arr[i];
    }

    int uniqueCount = removeDuplicates(duplicateArray, n);

    printf("\n7. Array after removing duplicates: ");
    printArray(duplicateArray, uniqueCount);

    /* 8. Reverse */
    int reverseArrayCopy[MAX];

    for (int i = 0; i < n; i++)
    {
        reverseArrayCopy[i] = arr[i];
    }

    reverseArray(reverseArrayCopy, n);

    printf("8. Reversed array: ");
    printArray(reverseArrayCopy, n);

    /* 9. Partition */
    printf("\nEnter pivot element for partition: ");
    scanf("%d", &pivot);

    int partitionCopy[MAX];

    for (int i = 0; i < n; i++)
    {
        partitionCopy[i] = arr[i];
    }

    partitionArray(partitionCopy, n, pivot);

    printf("9. Array after partitioning: ");
    printArray(partitionCopy, n);

    return 0;
}