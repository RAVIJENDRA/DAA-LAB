/* ============================================================
   Q6: Selection Sort + Loop Invariant
   ------------------------------------------------------------
   PSEUDOCODE (matches the question, 1-indexed A[1..n]):
       SELECTION-SORT(A, n)
         for i = 1 to n-1
             smallest = i
             for j = i+1 to n
                 if A[j] < A[smallest]
                     smallest = j
             exchange A[i] with A[smallest]

   LOOP INVARIANT (on the outer loop, checked before each iteration i):
       At the start of each iteration of the outer for loop,
       the subarray A[1..i-1] consists of the i-1 SMALLEST elements
       of the whole array, stored in sorted (non-decreasing) order.

     - Initialization: before the first iteration (i=1), A[1..0] is
       empty, so the invariant holds trivially (an empty subarray is
       vacuously "sorted" and contains the 0 smallest elements).
     - Maintenance: each iteration finds the smallest element of
       A[i..n] and swaps it into A[i]. Since A[1..i-1] already held
       the (i-1) smallest elements in order, and A[i] now holds the
       i-th smallest element (the min of everything else), A[1..i]
       now holds the i smallest elements in order -> invariant holds
       for i+1.
     - Termination: the loop ends when i = n. By the invariant,
       A[1..n-1] holds the (n-1) smallest elements in sorted order;
       the single remaining element A[n] must be the largest overall
       (whatever is left), so the WHOLE array A[1..n] is sorted.

   WHY ONLY (n-1) ITERATIONS, NOT n?
       After A[1..n-1] are the n-1 smallest elements in sorted order,
       there is exactly ONE element left (A[n]), and a single element
       is trivially "in its correct position" -- there's nothing left
       to compare it against or select. Running an nth iteration would
       search A[n..n] (a single element) for its own minimum and swap
       it with itself: it changes nothing, i.e. it is a wasted pass.

   COMPLEXITY:
       Inner loop always scans ALL remaining elements regardless of
       their order (there's no early exit / no way to detect the
       array is already sorted) -- so the number of COMPARISONS is
       always exactly  (n-1)+(n-2)+...+1 = n(n-1)/2 = Theta(n^2),
       for EVERY input. Best case is NOT better than worst case in
       terms of comparisons: Theta(n^2) either way (unlike, say,
       insertion sort, which IS O(n) on an already-sorted array).
       The only thing that can differ with input order is the number
       of SWAPS (0 on an already-sorted array vs up to n-1 otherwise)
       -- but swaps aren't the dominant cost here, comparisons are.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisons, swaps;

void selection_sort(int *a, int n){       /* 0-indexed version of the pseudocode above */
    for(int i=0;i<n-1;i++){
        int smallest=i;
        for(int j=i+1;j<n;j++){
            comparisons++;
            if(a[j]<a[smallest]) smallest=j;
        }
        if(smallest!=i){
            int t=a[i]; a[i]=a[smallest]; a[smallest]=t;
            swaps++;
        }
    }
}

int is_sorted(int *a,int n){ for(int i=1;i<n;i++) if(a[i-1]>a[i]) return 0; return 1; }

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int main(void){
    FILE *fp=fopen("results/q6_selection_sort.csv","w");
    fprintf(fp,"n,case,comparisons,swaps,theory_n_n_1_2,time_ns\n");

    int sizes[]={100,200,400,800,1600,3200,6400,12800};
    for(int s=0;s<8;s++){
        int n=sizes[s];

        /* CASE A: already sorted (best case for many other sorts, NOT for this one) */
        {
            int *a=malloc(n*sizeof(int));
            for(int i=0;i<n;i++) a[i]=i;
            comparisons=0; swaps=0;
            double t0=now_ns(); selection_sort(a,n); double t1=now_ns();
            printf("n=%6d [sorted input]   comparisons=%8ld  swaps=%6ld  theory n(n-1)/2=%8ld  %s\n",
                   n, comparisons, swaps, (long)n*(n-1)/2, is_sorted(a,n)?"OK":"BROKEN");
            fprintf(fp,"%d,sorted,%ld,%ld,%ld,%.0f\n", n, comparisons, swaps, (long)n*(n-1)/2, t1-t0);
            free(a);
        }
        /* CASE B: reverse sorted (worst case for swaps) */
        {
            int *a=malloc(n*sizeof(int));
            for(int i=0;i<n;i++) a[i]=n-i;
            comparisons=0; swaps=0;
            double t0=now_ns(); selection_sort(a,n); double t1=now_ns();
            printf("n=%6d [reverse input]  comparisons=%8ld  swaps=%6ld  theory n(n-1)/2=%8ld  %s\n",
                   n, comparisons, swaps, (long)n*(n-1)/2, is_sorted(a,n)?"OK":"BROKEN");
            fprintf(fp,"%d,reverse,%ld,%ld,%ld,%.0f\n", n, comparisons, swaps, (long)n*(n-1)/2, t1-t0);
            free(a);
        }
        /* CASE C: random */
        {
            int *a=malloc(n*sizeof(int));
            srand(42);
            for(int i=0;i<n;i++) a[i]=rand()%1000000;
            comparisons=0; swaps=0;
            double t0=now_ns(); selection_sort(a,n); double t1=now_ns();
            printf("n=%6d [random input]   comparisons=%8ld  swaps=%6ld  theory n(n-1)/2=%8ld  %s\n",
                   n, comparisons, swaps, (long)n*(n-1)/2, is_sorted(a,n)?"OK":"BROKEN");
            fprintf(fp,"%d,random,%ld,%ld,%ld,%.0f\n", n, comparisons, swaps, (long)n*(n-1)/2, t1-t0);
            free(a);
        }
    }
    fclose(fp);
    printf("\nNote: comparisons are IDENTICAL across sorted/reverse/random for each n\n");
    printf("(confirms best case is NOT better than worst case: always Theta(n^2) comparisons).\n");
    printf("Only swap counts differ (0 for already-sorted input).\n");
    printf("Wrote results/q6_selection_sort.csv\n");
    return 0;
}
