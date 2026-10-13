#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int start, end;
} Meeting;
int heap[10005], hs = 0;
int compare(const void *a, const void *b){
    Meeting *x = (Meeting *)a;
    Meeting *y = (Meeting *)b;
    return x->start - y->start;
}
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
int minRooms(Meeting a[], int n){
    int i, rooms = 0;
    hs = 0;
    qsort(a, n, sizeof(Meeting), compare);
    for (i = 0; i < n; i++){
        if (hs > 0 && heap[0] <= a[i].start)
            pop();
        push(a[i].end);
        if (hs > rooms)
            rooms = hs;
    }
    return rooms;
}
int main(){
    int n, i;
    Meeting *a;
    printf("Enter number of meetings: ");
    scanf("%d", &n);
    if (n <= 0){
        printf("Minimum rooms = 0\n");
        return 0;
    }
    a = (Meeting *)malloc(n * sizeof(Meeting));
    printf("Enter start and end times:\n");
    for (i = 0; i < n; i++)
        scanf("%d%d", &a[i].start, &a[i].end);
    printf("Minimum rooms = %d\n", minRooms(a, n));
    free(a);
    return 0;
}