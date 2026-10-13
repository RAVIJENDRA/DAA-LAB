#include <stdio.h>
#include <stdlib.h>
#define MAX 2000
int heap[MAX], hs = 0;
void push(int x){
    int i = hs++;
    while (i > 0 && heap[(i - 1) / 2] < x){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = x;
}
int pop(){
    int max = heap[0];
    int x = heap[--hs];
    int i = 0, child;
    while (2 * i + 1 < hs){
        child = 2 * i + 1;
        if (child + 1 < hs && heap[child + 1] > heap[child])
            child++;
        if (heap[child] <= x)
            break;
        heap[i] = heap[child];
        i = child;
    }
    if (hs > 0)
        heap[i] = x;
    return max;
}
int minDeviation(int arr[], int n){
    int i, x, minVal = 1000000000;
    int deviation = 1000000000;
    hs = 0;
    for (i = 0; i < n; i++){
        if (arr[i] % 2 != 0)
            arr[i] *= 2;
        push(arr[i]);
        if (arr[i] < minVal)
            minVal = arr[i];
    }
    while (hs > 0){
        x = pop();
        if (x - minVal < deviation)
            deviation = x - minVal;
        if (x % 2 != 0)
            break;
        x /= 2;
        if (x < minVal)
            minVal = x;
        push(x);
    }
    return deviation;
}
int main(){
    int n, i, *arr;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    if (n <= 0)
        return 0;
    arr = (int *)malloc(n * sizeof(int));
    printf("Enter array elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Minimum deviation = %d\n", minDeviation(arr, n));
    free(arr);
    return 0;
}