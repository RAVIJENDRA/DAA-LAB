#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int weight;
    float greedy;
    float fraction;
    int value, decay;
}element;
int compare(const void *a, const void *b) {
    element *x = (element *)a;
    element *y = (element *)b;
    if (x->greedy < y->greedy) return 1;
    if (x->greedy > y->greedy) return -1;
    return 0;
}
void calculateGreedy(element arr[], int n, int t) {
    for(int i=0;i<n; i++){
        arr[i].greedy =(float)arr[i].value / arr[i].weight- arr[i].decay * t;
        arr[i].fraction = 0.0;
    }
}
void knapsack(element arr[], int n, int wmax){
    int w = 0;
    qsort(arr, n, sizeof(element), compare);
    for (int i=0; i<n && w<wmax;i++) {
        if(arr[i].weight <= wmax - w){
            arr[i].fraction = 1.0;
            w += arr[i].weight;
        }else{
            arr[i].fraction = (float)(wmax - w) / arr[i].weight;
            w = wmax;
        }
    }
}
void display(element arr[], int n){
    for(int i=0;i<n;i++){
        printf("\nValue: %d\n", arr[i].value);
        printf("Weight: %d\n", arr[i].weight);
        printf("Greedy: %.2f\n", arr[i].greedy);
        printf("Fraction: %.2f\n", arr[i].fraction);
    }
}
int main(){
    int n, wmax, t;
    printf("Enter number of items: ");
    scanf("%d", &n);
    element *arr = malloc(n * sizeof(element));
    if(arr == NULL) return 1;
    for(int i=0;i<n;i++){
        printf("Enter value: ");
        scanf("%d", &arr[i].value);
        printf("Enter weight: ");
        scanf("%d", &arr[i].weight);
        printf("Enter decay rate: ");
        scanf("%d", &arr[i].decay);
    }
    printf("Enter capacity of knapsack: ");
    scanf("%d", &wmax);
    printf("Enter time: ");
    scanf("%d", &t);
    calculateGreedy(arr, n, t);
    knapsack(arr, n, wmax);
    display(arr, n);
    free(arr);
    return 0;
}
