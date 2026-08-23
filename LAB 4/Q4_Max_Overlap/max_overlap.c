/* ============================================================
   Q4: Application of Sorting-IV -- max simultaneous attendance,
       O(n log n)
   ------------------------------------------------------------
   INPUT:  n people, person i has entry time a_i and exit time b_i
           (b_i > a_i). All 2n times are distinct (no ties).
   OUTPUT: the time at which the most people were simultaneously
           present (and how many).

   ALGORITHM (classic sweep line):
     1. Build 2n EVENTS: an ENTRY event (+1) at each a_i, and an
        EXIT event (-1) at each b_i.
     2. Sort all 2n events by time                       -- O(n log n)
     3. Sweep left to right, maintaining a running count:
          on ENTRY: count++ ; if count is a new max, remember it
                     (the max can only increase right after an
                      entry, never after an exit)
          on EXIT:  count--
                                                          -- O(n)
   Total: O(n log n), dominated by the sort.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { int time; int type; /* +1 entry, -1 exit */ } Event;

int cmp_event(const void *a, const void *b){
    const Event *x=a, *y=b;
    return x->time - y->time;   /* all times distinct, so this alone is enough */
}

/* Fills *bestTime and *bestCount; returns nothing (void) since always succeeds for n>=1 */
void max_overlap(const int *entry, const int *exit_, int n, int *bestTime, int *bestCount){
    Event *ev = malloc(2*n*sizeof(Event));
    for(int i=0;i<n;i++){ ev[2*i]=(Event){entry[i], +1}; ev[2*i+1]=(Event){exit_[i], -1}; }
    qsort(ev, 2*n, sizeof(Event), cmp_event);      /* O(n log n) */

    int count=0, best=0, bestT=ev[0].time;
    for(int i=0;i<2*n;i++){                         /* O(n) */
        if(ev[i].type==+1){
            count++;
            if(count>best){ best=count; bestT=ev[i].time; }
        } else {
            count--;
        }
    }
    *bestTime=bestT; *bestCount=best;
    free(ev);
}

/* brute force reference: for each candidate time (every a_i), count
   how many intervals [a_j,b_j] contain it. O(n^2). Used only for testing. */
void max_overlap_brute(const int *entry, const int *exit_, int n, int *bestTime, int *bestCount){
    int best=0, bestT=entry[0];
    for(int i=0;i<n;i++){
        int t=entry[i], c=0;
        for(int j=0;j<n;j++) if(entry[j]<=t && t<exit_[j]) c++;
        if(c>best){ best=c; bestT=t; }
    }
    *bestTime=bestT; *bestCount=best;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int main(void){
    /* ---- hand-checkable demo ----
       Person A: 9:00-9:30, B: 9:10-10:00, C: 9:20-9:25, D: 9:50-10:10
       (using minutes-after-9:00 as integers: 0,30 / 10,60 / 20,25 / 50,70)
       At minute 20, A,B,C all present -> 3 simultaneous, the max. */
    int entry[]={0,10,20,50};
    int exitt[]={30,60,25,70};
    int n=4, bt, bc;
    max_overlap(entry, exitt, n, &bt, &bc);
    printf("Demo: entries={0,10,20,50}, exits={30,60,25,70}\n");
    printf("Max simultaneous attendance: %d people, achieved at t=%d\n\n", bc, bt);

    /* ---- correctness stress test vs O(n^2) brute force ---- */
    srand(3);
    int all_ok=1;
    for(int trial=0;trial<300;trial++){
        int nn=2+rand()%40;
        int *e=malloc(nn*sizeof(int)), *x=malloc(nn*sizeof(int));
        /* generate 2n distinct times, then pair them respecting entry<exit per person */
        int *pool=malloc(2*nn*sizeof(int));
        for(int i=0;i<2*nn;i++) pool[i]=i; /* distinct integers 0..2n-1 */
        for(int i=2*nn-1;i>0;i--){ int j=rand()%(i+1); int t=pool[i]; pool[i]=pool[j]; pool[j]=t; } /* shuffle */
        for(int i=0;i<nn;i++){
            int p1=pool[2*i], p2=pool[2*i+1];
            e[i]=p1<p2?p1:p2; x[i]=p1<p2?p2:p1;
        }
        int bt1,bc1,bt2,bc2;
        max_overlap(e,x,nn,&bt1,&bc1);
        max_overlap_brute(e,x,nn,&bt2,&bc2);
        if(bc1!=bc2){ all_ok=0; printf("MISMATCH trial=%d n=%d algo_count=%d brute_count=%d\n",trial,nn,bc1,bc2); }
        free(e); free(x); free(pool);
    }
    printf(all_ok? "All 300 randomized stress tests PASSED (matched brute force max COUNT).\n"
                  : "SOME STRESS TESTS FAILED.\n");

    /* ---- timing scaling ---- */
    FILE *fp=fopen("results/q4_timings.csv","w");
    fprintf(fp,"n,time_ns\n");
    int sizes[]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1000000};
    for(int s=0;s<11;s++){
        int nn=sizes[s];
        int *e=malloc(nn*sizeof(int)), *x=malloc(nn*sizeof(int));
        for(int i=0;i<nn;i++){ e[i]=2*i; x[i]=2*i+1+rand()%1000; } /* not overlap-heavy, but fine for timing */
        int bt,bc;
        double t0=now_ns();
        max_overlap(e,x,nn,&bt,&bc);
        double t1=now_ns();
        fprintf(fp,"%d,%.0f\n", nn, t1-t0);
        printf("n=%8d  time=%12.0f ns\n", nn, t1-t0);
        free(e); free(x);
    }
    fclose(fp);
    printf("Wrote results/q4_timings.csv\n");
    return 0;
}
