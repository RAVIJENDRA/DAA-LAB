#include <stdio.h>
#include <stdlib.h>
int heap[20005];
int hs = 0;
void push(int x){
    int i = hs++;
    while (i > 0 && heap[(i - 1) / 2] > x){
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i] = x;
}
int pop(){
    int min = heap[0];
    int x = heap[--hs];
    int i = 0, child;
    while (2 * i + 1 < hs){
        child = 2 * i + 1;
        if (child + 1 < hs && heap[child + 1] < heap[child])
            child++;
        if (heap[child] >= x)
            break;
        heap[i] = heap[child];
        i = child;
    }
    if (hs > 0)
        heap[i] = x;
    return min;
}
int minCost(int arr[], int n){
    int i, a, b, sum, cost = 0;
    hs = 0;
    for (i = 0; i < n; i++)
        push(arr[i]);
    while (hs > 1){
        a = pop();
        b = pop();
        sum = a + b;
        cost += sum;
        push(sum);
    }
    return cost;
}
int main(){
    int n, i, *arr;
    printf("Enter number of sticks: ");
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    printf("Enter stick lengths: ");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Minimum cost = %d\n", minCost(arr, n));
    free(arr);
    return 0;
}