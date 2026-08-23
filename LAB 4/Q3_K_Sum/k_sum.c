/* ============================================================
   Q3: Application of Sorting-III -- k numbers summing to T,
       in O(n^(k-1) . log n)
   ------------------------------------------------------------
   This DIRECTLY generalises Q2 (which is the k=2 case: sort O(n
   log n), then for the "other" element do a binary search -- total
   O(n log n) = O(n^(2-1) log n), matching the formula exactly).

   ALGORITHM:
     1. Sort S                                          -- O(n log n)
     2. Use (k-1) nested loops (implemented here as recursion, since
        k is a runtime parameter) to choose k-1 DISTINCT elements,
        with strictly increasing array indices to avoid re-testing
        the same combination in different orders
                                                 -- O(n^(k-1)) combinations
     3. For each combination, BINARY SEARCH for the single remaining
        value  (T - sum of the chosen k-1 elements)  in the sorted
        array                                    -- O(log n) per combination
     If a valid, distinct k-th index is found, report success.

   Total: O(n log n) + O(n^(k-1)) * O(log n) = O(n^(k-1) . log n)
   for any fixed k >= 2 (the initial sort is dominated for k >= 2).

   NOTE on duplicate values: if the target value appears multiple
   times in the sorted array, binary search only lands on ONE
   occurrence; we scan left/right through the block of equal values
   to find one whose index isn't already used by this combination.
   For inputs without long runs of duplicate values this adds only
   O(1) amortised work per check; it is a linear scan ONLY within a
   block of equal values, not the whole array.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXK 10

int cmp_int(const void *a, const void *b){ return (*(int*)a)-(*(int*)b); }

/* Finds an index of value `need` in sorted[0..n-1] that is NOT
   already in usedIdx[0..usedCount-1]. Returns -1 if none exists. */
int find_unused_occurrence(const int *sorted, int n, int need, const int *usedIdx, int usedCount){
    int lo=0, hi=n-1, pos=-1;
    while(lo<=hi){                                   /* O(log n) binary search */
        int mid=lo+(hi-lo)/2;
        if(sorted[mid]==need){ pos=mid; break; }
        else if(sorted[mid]<need) lo=mid+1; else hi=mid-1;
    }
    if(pos==-1) return -1;
    for(int l=pos; l>=0 && sorted[l]==need; l--){     /* scan the equal-value block */
        int used=0;
        for(int i=0;i<usedCount;i++) if(usedIdx[i]==l){ used=1; break; }
        if(!used) return l;
    }
    for(int r=pos+1; r<n && sorted[r]==need; r++){
        int used=0;
        for(int i=0;i<usedCount;i++) if(usedIdx[i]==r){ used=1; break; }
        if(!used) return r;
    }
    return -1;
}

/* recursively choose k-1 increasing indices, then binary-search the last */
int recurse(const int *sorted, int n, int k, long T, int *chosen, int depth, int start, long partialSum){
    if(depth==k-1){
        long need = T - partialSum;
        if(need < -2000000000L || need > 2000000000L) return 0; /* overflow guard */
        int idx = find_unused_occurrence(sorted, n, (int)need, chosen, depth);
        if(idx!=-1){ chosen[depth]=idx; return 1; }
        return 0;
    }
    for(int i=start; i<=n-(k-1-depth); i++){
        chosen[depth]=i;
        if(recurse(sorted,n,k,T,chosen,depth+1,i+1,partialSum+sorted[i])) return 1;
    }
    return 0;
}

/* Returns 1 if some k elements of S sum to T (and fills `result` with
   them); else 0. Handles k==1 as a trivial direct search. */
int k_sum_exists(const int *S, int n, int k, long T, int *result){
    int *sorted = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) sorted[i]=S[i];
    qsort(sorted, n, sizeof(int), cmp_int);            /* O(n log n) */

    if(k==1){
        int idx = find_unused_occurrence(sorted,n,(int)T,NULL,0);
        if(idx!=-1){ result[0]=sorted[idx]; free(sorted); return 1; }
        free(sorted); return 0;
    }
    int chosen[MAXK];
    int found = recurse(sorted, n, k, T, chosen, 0, 0, 0);
    if(found) for(int i=0;i<k;i++) result[i]=sorted[chosen[i]];
    free(sorted);
    return found;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int main(void){
    /* ---- hand-checkable demo ---- */
    int S[]={2,4,5,9,12,15,20}; int n=7;
    int result[MAXK];

    for(int k=2; k<=4; k++){
        long T = (k==2)? 24 : (k==3)? 26 : 40; /* chosen to have a known solution */
        int found = k_sum_exists(S,n,k,T,result);
        printf("k=%d, T=%ld -> %s", k, T, found? "FOUND: ":"NOT FOUND\n");
        if(found){
            for(int i=0;i<k;i++) printf("%d%s", result[i], i<k-1?" + ":" = ");
            printf("%ld\n", T);
        }
    }
    printf("\n");

    /* ---- correctness stress test vs brute force (small n, k=2,3,4) ---- */
    srand(42);
    int all_ok=1, tested=0;
    for(int trial=0; trial<150; trial++){
        int nn = 4 + rand()%10;
        int kk = 2 + rand()%3; /* k in {2,3,4} */
        if(nn < kk) continue;
        int *A = malloc(nn*sizeof(int));
        for(int i=0;i<nn;i++) A[i]=rand()%30 - 5;
        long T = rand()%80 - 20;

        /* brute force: try all C(nn,kk) combinations directly on A */
        int idxs[MAXK];
        int brute=0;
        /* simple recursive brute forcer */
        void brute_rec(int start,int d,long s){
            if(brute) return;
            if(d==kk){ if(s==T) brute=1; return; }
            for(int i=start;i<nn;i++) brute_rec(i+1,d+1,s+A[i]);
        }
        brute_rec(0,0,0);

        int algoFound = k_sum_exists(A,nn,kk,T,idxs);
        tested++;
        if(algoFound!=brute){
            all_ok=0;
            printf("MISMATCH trial=%d n=%d k=%d T=%ld brute=%d algo=%d\n",trial,nn,kk,T,brute,algoFound);
        } else if(algoFound){
            long s=0; for(int i=0;i<kk;i++) s+=idxs[i];
            if(s!=T){ all_ok=0; printf("BAD SUM trial=%d\n",trial); }
        }
        free(A);
    }
    printf(all_ok? "All %d randomized stress tests (k=2..4) PASSED (matched brute force).\n" : "SOME STRESS TESTS FAILED.\n", tested);

    /* ---- timing scaling for fixed k=3: expect ~ n^2 log n growth ---- */
    FILE *fp=fopen("results/q3_timings.csv","w");
    fprintf(fp,"n,k,time_ns\n");
    int sizes[]={50,80,120,180,270,400,600,900,1300,2000};
    for(int s=0;s<10;s++){
        int nn=sizes[s];
        int *A=malloc(nn*sizeof(int));
        for(int i=0;i<nn;i++) A[i]=rand()%1000000;
        long T=-999999; /* guaranteed absent (all values non-negative) -> true worst case */
        int res[MAXK];
        double t0=now_ns();
        k_sum_exists(A,nn,3,T,res);
        double t1=now_ns();
        fprintf(fp,"%d,3,%.0f\n", nn, t1-t0);
        printf("n=%6d k=3  time=%14.0f ns\n", nn, t1-t0);
        free(A);
    }
    fclose(fp);
    printf("Wrote results/q3_timings.csv\n");
    return 0;
}
