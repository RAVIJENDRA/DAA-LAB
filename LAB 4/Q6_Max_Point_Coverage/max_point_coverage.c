/* ============================================================
   Q6: Application of Sorting-VI -- point covered by the most
       intervals, O(n log n)
   ------------------------------------------------------------
   INPUT:  n intervals [l_i, r_i] on a line (endpoints INCLUDED
           in the interval, so a point exactly at l_i or r_i still
           counts as being inside).
   OUTPUT: a point p covered by the maximum number of intervals,
           and that count.

   ALGORITHM (sweep line, careful with the inclusive endpoints):
     1. Build 2n events: a START event (+1) at each l_i, and an
        END event (-1) at each r_i.
     2. Sort events by coordinate; when coordinates TIE, process
        ALL starts at that coordinate BEFORE any end at that same
        coordinate.
                                                          -- O(n log n)
     3. Sweep in that order, maintaining a running count:
          on START: count++ ; check for a new max right here
          on END:   count--
                                                          -- O(n)

   WHY START-BEFORE-END ON TIES MATTERS: if interval A ends at
   coordinate c and interval B starts at coordinate c, BOTH are
   present at the point c (endpoints are inclusive on both sides).
   Processing B's start before A's end ensures the running count
   reflects both of them being active at c at the same time -- if
   we processed the end first we would undercount by 1 at that
   exact point.

   Total: O(n log n), dominated by the sort.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int coord; int type; /* +1 = start, -1 = end */ } Event;

int cmp_event(const void *a, const void *b){
    const Event *x=a, *y=b;
    if(x->coord != y->coord) return x->coord - y->coord;
    return y->type - x->type;    /* +1 (start) sorts before -1 (end) when tied */
}

/* Fills *bestPoint, *bestCount. */
void max_point_coverage(const int *l, const int *r, int n, int *bestPoint, int *bestCount){
    Event *ev = malloc(2*n*sizeof(Event));
    for(int i=0;i<n;i++){ ev[2*i]=(Event){l[i], +1}; ev[2*i+1]=(Event){r[i], -1}; }
    qsort(ev, 2*n, sizeof(Event), cmp_event);          /* O(n log n) */

    int count=0, best=0, bestP=ev[0].coord;
    for(int i=0;i<2*n;i++){                              /* O(n) */
        if(ev[i].type==+1){
            count++;
            if(count>best){ best=count; bestP=ev[i].coord; }
        } else {
            count--;
        }
    }
    *bestPoint=bestP; *bestCount=best;
    free(ev);
}

/* brute force reference: try every endpoint as a candidate point (the
   optimum is always achievable at some endpoint), count containment. O(n^2) */
void max_point_coverage_brute(const int *l, const int *r, int n, int *bestPoint, int *bestCount){
    int best=0, bestP=l[0];
    for(int i=0;i<n;i++){
        int cands[2]={l[i], r[i]};
        for(int c=0;c<2;c++){
            int p=cands[c], cnt=0;
            for(int j=0;j<n;j++) if(l[j]<=p && p<=r[j]) cnt++;
            if(cnt>best){ best=cnt; bestP=p; }
        }
    }
    *bestPoint=bestP; *bestCount=best;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int main(void){
    /* ---- exact example from the problem statement ---- */
    int l[]={10,20,50,15}, r[]={40,60,90,70};
    int n=4, bp, bc;
    max_point_coverage(l,r,n,&bp,&bc);
    printf("Demo: S = {(10,40),(20,60),(50,90),(15,70)}\n");
    printf("Point covered by most intervals: p=%d, count=%d\n", bp, bc);
    printf("(Problem statement notes p=50 gives 3 -- any point with count 3 is a valid answer)\n\n");

    /* ---- correctness stress test vs brute force ---- */
    srand(5);
    int all_ok=1;
    for(int trial=0;trial<300;trial++){
        int nn=1+rand()%30;
        int *ll=malloc(nn*sizeof(int)), *rr=malloc(nn*sizeof(int));
        for(int i=0;i<nn;i++){ int a=rand()%60; int len=rand()%20; ll[i]=a; rr[i]=a+len; }
        int p1,c1,p2,c2;
        max_point_coverage(ll,rr,nn,&p1,&c1);
        max_point_coverage_brute(ll,rr,nn,&p2,&c2);
        if(c1!=c2){ all_ok=0; printf("MISMATCH trial=%d n=%d algo_count=%d brute_count=%d\n",trial,nn,c1,c2); }
        free(ll); free(rr);
    }
    printf(all_ok? "All 300 randomized stress tests PASSED (matched brute force max COUNT).\n"
                  : "SOME STRESS TESTS FAILED.\n");

    /* ---- timing scaling ---- */
    FILE *fp=fopen("results/q6_timings.csv","w");
    fprintf(fp,"n,time_ns\n");
    int sizes[]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1000000};
    for(int s=0;s<11;s++){
        int nn=sizes[s];
        int *ll=malloc(nn*sizeof(int)), *rr=malloc(nn*sizeof(int));
        for(int i=0;i<nn;i++){ int a=rand()%(nn*2); ll[i]=a; rr[i]=a+1+rand()%50; }
        int bp2,bc2;
        double t0=now_ns();
        max_point_coverage(ll,rr,nn,&bp2,&bc2);
        double t1=now_ns();
        fprintf(fp,"%d,%.0f\n", nn, t1-t0);
        printf("n=%8d  time=%12.0f ns\n", nn, t1-t0);
        free(ll); free(rr);
    }
    fclose(fp);
    printf("Wrote results/q6_timings.csv\n");
    return 0;
}
