#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int distance, fuel;
} Station;
int compare(const void *a, const void *b) {
    Station *x = (Station *)a;
    Station *y = (Station *)b;
    return x->distance - y->distance;
}
int heap[10005], hs = 0;
void push(int x) {
    int i = ++hs;
    while (i > 1 && heap[i / 2] < x) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;
}
int pop() {
    int ans = heap[1];
    int x = heap[hs--], i = 1, c;
    while (2 * i <= hs) {
        c = 2 * i;
        if (c < hs && heap[c + 1] > heap[c])
            c++;
        if (x >= heap[c])
            break;
        heap[i] = heap[c];
        i = c;
    }
    if (hs > 0)
        heap[i] = x;
    return ans;
}
int minStops(Station a[], int n, int D, int F) {
    int stops = 0, prev = 0;
    for (int i = 0; i <= n; i++) {
        int distance = (i == n) ? D : a[i].distance;
        F -= distance - prev;
        while (F < 0 && hs > 0) {
            F += pop();
            stops++;
        }
        if (F < 0)
            return -1;
        if (i < n)
            push(a[i].fuel);
        prev = distance;
    }
    return stops;
}
int main() {
    int n, D, F;
    printf("Enter number of stations: ");
    scanf("%d", &n);
    Station a[n];
    for (int i = 0; i < n; i++) {
        printf("Enter distance and fuel: ");
        scanf("%d %d", &a[i].distance, &a[i].fuel);
    }
    printf("Enter target distance and initial fuel: ");
    scanf("%d %d", &D, &F);
    qsort(a, n, sizeof(Station), compare);
    int ans = minStops(a, n, D, F);
    if (ans == -1)
        printf("Destination cannot be reached\n");
    else
        printf("Minimum refuelling stops = %d\n", ans);
    return 0;
}