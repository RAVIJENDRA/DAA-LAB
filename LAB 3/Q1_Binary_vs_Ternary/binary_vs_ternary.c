/* ============================================================
   Q1: Binary Search vs Ternary Search
   ------------------------------------------------------------
   Both search a SORTED array of size n for a value x.
   We count "probes" = number of array elements actually compared
   against x (this is the fair, standard way to compare the two
   algorithms, independent of how many if-statements the C code
   happens to use).

   THEORY:
     Binary search:  1 probe per level, search space /2 each time
                      -> worst case = floor(log2 n) + 1 probes
     Ternary search: 2 probes per level, search space /3 each time
                      -> worst case = 2*ceil(log3 n) probes
                      = 2 * log(n)/log(3) = (2/1.585)*log2(n) ~ 1.26*log2(n)

   So even though ternary shrinks the search space *faster* per
   level (divide by 3 instead of 2), it needs *more* probes per
   level (2 instead of 1), and 2*log3(n) > log2(n) for all n>1.
   Binary search wins. This program measures actual probe counts
   for both, for the worst case (element absent from the array),
   across increasing n, and writes them to a CSV for plotting
   against the two theoretical curves.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ---------------- Binary search ---------------- */
int binary_search(int *a, int n, int x, long *probes){
    int lo=0, hi=n-1;
    while(lo<=hi){
        int mid=lo+(hi-lo)/2;
        (*probes)++;
        if(a[mid]==x) return mid;
        if(a[mid]<x) lo=mid+1; else hi=mid-1;
    }
    return -1;
}

/* ---------------- Ternary search ---------------- */
int ternary_search(int *a, int n, int x, long *probes){
    int lo=0, hi=n-1;
    while(lo<=hi){
        int third=(hi-lo)/3;
        int m1=lo+third;
        int m2=hi-third;
        (*probes)++;
        if(a[m1]==x) return m1;
        (*probes)++;
        if(a[m2]==x) return m2;
        if(x<a[m1]) hi=m1-1;
        else if(x>a[m2]) lo=m2+1;
        else { lo=m1+1; hi=m2-1; }
    }
    return -1;
}

int main(void){
    FILE *fp=fopen("results/q1_comparisons.csv","w");
    fprintf(fp,"n,binary_probes,ternary_probes,theory_binary,theory_ternary\n");

    for(int n=8; n<=200000; n = n*2){
        int *a=malloc(n*sizeof(int));
        for(int i=0;i<n;i++) a[i]=2*i;   /* sorted, only even numbers -> odd x is always absent (true worst case) */

        /* worst case: search for a value guaranteed absent, and also
           average over several such absent probes across the array's range */
        long total_b=0, total_t=0;
        int trials=25;
        for(int t=0;t<trials;t++){
            int x = 1 + (int)((long)t * (2L*n) / trials); /* odd-ish spread, always absent since array has evens */
            if(x%2==0) x++;
            long pb=0, pt=0;
            binary_search(a,n,x,&pb);
            ternary_search(a,n,x,&pt);
            total_b+=pb; total_t+=pt;
        }
        double avg_b=(double)total_b/trials;
        double avg_t=(double)total_t/trials;
        double theory_b=floor(log2((double)n))+1;
        double theory_t=2*ceil(log((double)n)/log(3.0));

        fprintf(fp,"%d,%.2f,%.2f,%.2f,%.2f\n", n, avg_b, avg_t, theory_b, theory_t);
        printf("n=%7d  binary=%.2f (theory %.2f)   ternary=%.2f (theory %.2f)\n",
               n, avg_b, theory_b, avg_t, theory_t);

        free(a);
    }
    fclose(fp);
    printf("Wrote results/q1_comparisons.csv\n");
    return 0;
}
