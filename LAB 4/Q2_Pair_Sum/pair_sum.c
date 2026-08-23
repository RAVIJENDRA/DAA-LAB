/* ============================================================
   Q2: Application of Sorting-II -- pair summing to x, O(n log n)
   ------------------------------------------------------------
   INPUT:  two sets S1, S2 (each size n), and a target x.
   OUTPUT: whether there exist a in S1, b in S2 with a+b = x
           (and if so, one such pair).

   ALGORITHM:
     1. Sort S1                                    -- O(n log n)
     2. For each b in S2, BINARY SEARCH for (x - b) in sorted S1
                                                     -- O(n log n) total
     If found for any b, report the pair.

   Total: O(n log n). (An alternative O(n log n) method sorts BOTH
   sets and uses a two-pointer sweep in O(n) after the sorts --
   also valid and included below for comparison -- but the
   "sort one side, binary-search with the other" version is what
   we deliberately generalise in Q3, since it is the version whose
   complexity scales to O(n^(k-1) log n) for k elements.)
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp_int(const void *a, const void *b){ return (*(int*)a) - (*(int*)b); }

/* binary search for `target` in sorted array a[0..n-1]; returns index or -1 */
int binary_search(const int *a, int n, int target){
    int lo=0, hi=n-1;
    while(lo<=hi){
        int mid=lo+(hi-lo)/2;
        if(a[mid]==target) return mid;
        if(a[mid]<target) lo=mid+1; else hi=mid-1;
    }
    return -1;
}

/* returns 1 and sets *outA,*outB if a pair is found, else returns 0 */
int find_pair_sum(int *S1, int n1, int *S2, int n2, int x, int *outA, int *outB){
    int *sorted1 = malloc(n1*sizeof(int));
    for(int i=0;i<n1;i++) sorted1[i]=S1[i];
    qsort(sorted1, n1, sizeof(int), cmp_int);          /* O(n log n) */

    for(int j=0;j<n2;j++){                              /* O(n) iterations */
        int need = x - S2[j];
        int idx = binary_search(sorted1, n1, need);      /* O(log n) each */
        if(idx!=-1){ *outA=sorted1[idx]; *outB=S2[j]; free(sorted1); return 1; }
    }
    free(sorted1);
    return 0;
}

/* --------- alternative O(n log n): sort both, two-pointer sweep --------- */
int find_pair_sum_twopointer(int *S1, int n1, int *S2, int n2, int x, int *outA, int *outB){
    int *a=malloc(n1*sizeof(int)); for(int i=0;i<n1;i++) a[i]=S1[i];
    int *b=malloc(n2*sizeof(int)); for(int i=0;i<n2;i++) b[i]=S2[i];
    qsort(a,n1,sizeof(int),cmp_int);
    qsort(b,n2,sizeof(int),cmp_int);
    int i=0, j=n2-1;
    while(i<n1 && j>=0){
        int sum=a[i]+b[j];
        if(sum==x){ *outA=a[i]; *outB=b[j]; free(a); free(b); return 1; }
        else if(sum<x) i++; else j--;
    }
    free(a); free(b);
    return 0;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int main(void){
    /* ---- demo from a hand-checkable example ---- */
    int S1[]={1,4,6,9,15}, S2[]={2,5,7,10,20};
    int n1=5, n2=5, x=11, a,b;
    int found = find_pair_sum(S1,n1,S2,n2,x,&a,&b);
    printf("Demo: S1={1,4,6,9,15}, S2={2,5,7,10,20}, x=11\n");
    printf("Result: %s", found? "FOUND ":"NOT FOUND");
    if(found) printf("-> %d (from S1) + %d (from S2) = %d\n", a,b,a+b);
    else printf("\n");

    int x2=100; /* no pair should sum to 100 here */
    found = find_pair_sum(S1,n1,S2,n2,x2,&a,&b);
    printf("Demo: x=100 -> %s\n\n", found? "FOUND (unexpected!)":"correctly NOT FOUND");

    /* ---- correctness stress test: brute force O(n^2) reference ---- */
    srand(7);
    int all_ok=1;
    for(int trial=0; trial<200; trial++){
        int n = 5 + rand()%40;
        int *A=malloc(n*sizeof(int)), *B=malloc(n*sizeof(int));
        for(int i=0;i<n;i++){ A[i]=rand()%200-100; B[i]=rand()%200-100; }
        int target = rand()%400-200;

        int bruteFound=0;
        for(int i=0;i<n && !bruteFound;i++)
            for(int j=0;j<n;j++)
                if(A[i]+B[j]==target){ bruteFound=1; break; }

        int aa,bb;
        int algoFound = find_pair_sum(A,n,B,n,target,&aa,&bb);
        int algo2Found = find_pair_sum_twopointer(A,n,B,n,target,&aa,&bb);

        if(algoFound!=bruteFound || algo2Found!=bruteFound){
            all_ok=0;
            printf("MISMATCH trial=%d n=%d target=%d brute=%d algo1=%d algo2=%d\n",
                   trial,n,target,bruteFound,algoFound,algo2Found);
        }
        if(algoFound){
            if(aa+bb!=target){ all_ok=0; printf("BAD PAIR trial=%d\n",trial); }
        }
        free(A); free(B);
    }
    printf(all_ok? "All 200 randomized stress tests PASSED (matched brute force).\n"
                  : "SOME STRESS TESTS FAILED.\n");

    /* ---- timing scaling ---- */
    FILE *fp=fopen("results/q2_timings.csv","w");
    fprintf(fp,"n,time_ns\n");
    int sizes[]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1000000};
    for(int s=0;s<11;s++){
        int n=sizes[s];
        int *A=malloc(n*sizeof(int)), *B=malloc(n*sizeof(int));
        for(int i=0;i<n;i++){ A[i]=rand(); B[i]=rand(); }
        int target = -1; /* guaranteed absent (all values non-negative from rand()) -> true worst case */
        int aa,bb;
        double t0=now_ns();
        find_pair_sum(A,n,B,n,target,&aa,&bb);
        double t1=now_ns();
        fprintf(fp,"%d,%.0f\n", n, t1-t0);
        printf("n=%8d  time=%12.0f ns\n", n, t1-t0);
        free(A); free(B);
    }
    fclose(fp);
    printf("Wrote results/q2_timings.csv\n");
    return 0;
}
