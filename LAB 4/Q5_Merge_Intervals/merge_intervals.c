/* ============================================================
   Q5: Application of Sorting-V -- merge overlapping intervals,
       O(n log n)
   ------------------------------------------------------------
   INPUT:  a list I of n intervals (x_i, y_i).
   OUTPUT: the minimal list of intervals covering the same set of
           points, with all overlaps merged.

   ALGORITHM:
     1. Sort the intervals by their LEFT endpoint x_i    -- O(n log n)
     2. Scan left to right, keeping a "current" merged interval:
          - if the next interval's start <= current interval's end,
            they overlap (or touch) -> extend current's end to
            max(current.end, next.end)
          - otherwise the current interval is finished -> emit it,
            and start a new "current" = next interval
                                                          -- O(n)
   Total: O(n log n), dominated by the sort.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int x, y; } Interval;

int cmp_interval(const void *a, const void *b){
    const Interval *p=a, *q=b;
    return p->x - q->x;
}

/* Merges `in` (n intervals) into `out` (caller-allocated, size >= n).
   Returns the number of intervals in the merged result. */
int merge_intervals(Interval *in, int n, Interval *out){
    if(n==0) return 0;
    Interval *sorted = malloc(n*sizeof(Interval));
    for(int i=0;i<n;i++) sorted[i]=in[i];
    qsort(sorted, n, sizeof(Interval), cmp_interval);   /* O(n log n) */

    int m=0;
    out[0]=sorted[0];
    for(int i=1;i<n;i++){                                 /* O(n) */
        if(sorted[i].x <= out[m].y){                       /* overlap/touch */
            if(sorted[i].y > out[m].y) out[m].y = sorted[i].y;
        } else {
            m++;
            out[m]=sorted[i];
        }
    }
    free(sorted);
    return m+1;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

/* brute force reference: repeatedly merge any overlapping pair. O(n^3)-ish, fine for small n */
int merge_brute(Interval *in, int n, Interval *out){
    Interval *cur = malloc(n*sizeof(Interval));
    for(int i=0;i<n;i++) cur[i]=in[i];
    int m=n;
    int changed=1;
    while(changed){
        changed=0;
        for(int i=0;i<m && !changed;i++)
            for(int j=i+1;j<m;j++){
                int lo1=cur[i].x, hi1=cur[i].y, lo2=cur[j].x, hi2=cur[j].y;
                if(lo1<=hi2 && lo2<=hi1){ /* overlap */
                    int nx = lo1<lo2?lo1:lo2, ny = hi1>hi2?hi1:hi2;
                    cur[i].x=nx; cur[i].y=ny;
                    cur[j]=cur[m-1]; m--;
                    changed=1; break;
                }
            }
    }
    for(int i=0;i<m;i++) out[i]=cur[i];
    free(cur);
    /* sort output by x for stable comparison against the main algorithm */
    qsort(out, m, sizeof(Interval), cmp_interval);
    return m;
}

int main(void){
    /* ---- exact example from the problem statement ---- */
    Interval demo[] = {{1,3},{2,6},{8,10},{7,18}};
    int n=4;
    Interval out[10];
    int m = merge_intervals(demo, n, out);
    printf("Demo: I = {(1,3),(2,6),(8,10),(7,18)}\n");
    printf("Merged (%d intervals): ", m);
    for(int i=0;i<m;i++) printf("(%d,%d) ", out[i].x, out[i].y);
    printf("\nExpected:                 (1,6) (7,18)\n\n");

    /* ---- correctness stress test vs brute force ---- */
    srand(11);
    int all_ok=1;
    for(int trial=0;trial<300;trial++){
        int nn=1+rand()%25;
        Interval *in=malloc(nn*sizeof(Interval));
        for(int i=0;i<nn;i++){
            int a=rand()%50;
            int len=1+rand()%15;
            in[i].x=a; in[i].y=a+len;
        }
        Interval *o1=malloc(nn*sizeof(Interval)), *o2=malloc(nn*sizeof(Interval));
        int m1=merge_intervals(in,nn,o1);
        int m2=merge_brute(in,nn,o2);
        int ok = (m1==m2);
        if(ok) for(int i=0;i<m1;i++) if(o1[i].x!=o2[i].x || o1[i].y!=o2[i].y) ok=0;
        if(!ok){ all_ok=0; printf("MISMATCH trial=%d n=%d m1=%d m2=%d\n",trial,nn,m1,m2); }
        free(in); free(o1); free(o2);
    }
    printf(all_ok? "All 300 randomized stress tests PASSED (matched brute force).\n"
                  : "SOME STRESS TESTS FAILED.\n");

    /* ---- timing scaling ---- */
    FILE *fp=fopen("results/q5_timings.csv","w");
    fprintf(fp,"n,time_ns\n");
    int sizes[]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1000000};
    for(int s=0;s<11;s++){
        int nn=sizes[s];
        Interval *in=malloc(nn*sizeof(Interval)), *out2=malloc(nn*sizeof(Interval));
        for(int i=0;i<nn;i++){ int a=rand()%(nn*2); in[i].x=a; in[i].y=a+1+rand()%20; }
        double t0=now_ns();
        merge_intervals(in,nn,out2);
        double t1=now_ns();
        fprintf(fp,"%d,%.0f\n", nn, t1-t0);
        printf("n=%8d  time=%12.0f ns\n", nn, t1-t0);
        free(in); free(out2);
    }
    fclose(fp);
    printf("Wrote results/q5_timings.csv\n");
    return 0;
}
