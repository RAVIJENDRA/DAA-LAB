/* ============================================================
   Q3: Simultaneous Max & Min via Divide and Conquer
   Bound to prove/validate:  at most ceil(3n/2) - 2 comparisons

   Standard trick: comparing elements in PAIRS first (1 comparison
   to find the smaller/larger of each pair) lets us then only
   compare "the smaller ones" against the running min and "the
   larger ones" against the running max -- avoiding the naive 2(n-1)
   comparisons of a linear scan.

   Recurrence (D&C form):
     n<=1 : 0 comparisons            (single element is both max & min)
     n==2 : 1 comparison             (compare the pair directly)
     else : T(n) = 2*T(n/2) + 2      (split, recurse both halves,
                                       2 more comparisons to merge:
                                       max(max1,max2), min(min1,min2))
   Solving T(n) = 2T(n/2)+2 with T(2)=1 gives, for n = 2^k:
        T(n) = 3n/2 - 2
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long comparisons;

typedef struct { int mx, mn; } Pair;

Pair maxmin(int *a, int lo, int hi){
    int n = hi-lo+1;
    Pair r;
    if(n==1){ r.mx=r.mn=a[lo]; return r; }
    if(n==2){
        comparisons++;
        if(a[lo]>a[hi]){ r.mx=a[lo]; r.mn=a[hi]; } else { r.mx=a[hi]; r.mn=a[lo]; }
        return r;
    }
    int mid=lo+(hi-lo)/2;
    Pair L=maxmin(a,lo,mid);
    Pair R=maxmin(a,mid+1,hi);
    Pair out;
    comparisons++; out.mx = (L.mx>R.mx)? L.mx : R.mx;
    comparisons++; out.mn = (L.mn<R.mn)? L.mn : R.mn;
    return out;
}

int* random_array(int n, unsigned seed){
    int *a=malloc(n*sizeof(int));
    srand(seed);
    for(int i=0;i<n;i++) a[i]=rand()%1000000;
    return a;
}

int main(void){
    FILE *fp=fopen("results/q3_comparisons.csv","w");
    fprintf(fp,"n,comparisons,bound_3n_2\n");

    int all_ok=1;
    for(int n=2;n<=1<<20; n*=2){
        int *a=random_array(n, 123);
        comparisons=0;
        Pair res = maxmin(a,0,n-1);

        /* correctness check against a trivial linear scan */
        int truemax=a[0], truemin=a[0];
        for(int i=1;i<n;i++){ if(a[i]>truemax) truemax=a[i]; if(a[i]<truemin) truemin=a[i]; }
        int ok = (res.mx==truemax && res.mn==truemin);
        if(!ok){ all_ok=0; printf("MISMATCH at n=%d\n", n); }

        double bound = 3.0*n/2.0 - 2;
        fprintf(fp,"%d,%ld,%.1f\n", n, comparisons, bound);
        printf("n=%8d  comparisons=%8ld   bound(3n/2 - 2)=%10.1f   %s\n",
               n, comparisons, bound, (comparisons<=(long)(bound+0.5))? "OK (within bound)":"VIOLATION");
        free(a);
    }
    fclose(fp);
    printf(all_ok? "\nAll results correct (matched linear-scan max/min).\n" : "\nSOME RESULTS WRONG.\n");
    printf("Wrote results/q3_comparisons.csv\n");
    return 0;
}
