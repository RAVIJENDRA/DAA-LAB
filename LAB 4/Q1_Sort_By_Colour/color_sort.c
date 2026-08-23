/* ============================================================
   Q1: Application of Sorting-I  --  Sort by colour in O(n)
   ------------------------------------------------------------
   INPUT:  n pairs (number, colour), colour in {RED, BLUE, YELLOW},
           already sorted by number.
   OUTPUT: the same pairs reordered so all REDs come first, then
           all BLUEs, then all YELLOWs -- and within each colour
           group the numbers must still be in sorted order.

   KEY INSIGHT: there are only 3 possible colours -- a CONSTANT --
   so this is really just a 3-bucket counting sort keyed on colour,
   NOT a general comparison sort. Because the input is already
   sorted by number, simply streaming items into their colour's
   bucket IN INPUT ORDER automatically keeps each bucket sorted by
   number too (we never need to compare numbers against each other
   at all).

   ALGORITHM (single pass, like counting sort's placement step):
     1. Count how many items of each colour there are   -- O(n)
     2. Compute each colour's starting offset in the output
        array: RED starts at 0, BLUE starts right after all the
        REDs, YELLOW starts right after all the BLUEs           -- O(1)
     3. Scan the input once more, left to right (i.e. in
        increasing-number order); place each item at its colour's
        next free slot and advance that colour's slot pointer     -- O(n)

   Total: O(n) time, O(n) auxiliary space, and STABLE (numbers stay
   sorted within each colour group) precisely because step 3 visits
   items in increasing-number order and never reorders within a
   bucket.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { RED=0, BLUE=1, YELLOW=2 } Colour;
const char* colour_name(Colour c){ return c==RED?"RED":c==BLUE?"BLUE":"YELLOW"; }

typedef struct { int number; Colour colour; } Item;

/* The O(n) algorithm described above. `in` must already be sorted
   by `number`. Result is written into `out` (caller-allocated, size n). */
void sort_by_colour(Item *in, int n, Item *out){
    int count[3] = {0,0,0};
    for(int i=0;i<n;i++) count[in[i].colour]++;          /* pass 1: O(n) */

    int offset[3];
    offset[RED]=0;
    offset[BLUE]=offset[RED]+count[RED];
    offset[YELLOW]=offset[BLUE]+count[BLUE];              /* O(1) */

    int next[3] = { offset[RED], offset[BLUE], offset[YELLOW] };
    for(int i=0;i<n;i++){                                 /* pass 2: O(n) */
        Colour c = in[i].colour;
        out[next[c]++] = in[i];
    }
}

/* ---------------- validation ---------------- */
int is_valid_result(Item *out, int n){
    /* 1) all REDs before all BLUEs before all YELLOWs */
    for(int i=1;i<n;i++) if(out[i-1].colour > out[i].colour) return 0;
    /* 2) within each colour, numbers strictly increasing (stability) */
    for(int i=1;i<n;i++)
        if(out[i-1].colour==out[i].colour && out[i-1].number > out[i].number) return 0;
    return 1;
}

static double now_ns(void){
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts);
    return (double)ts.tv_sec*1e9+(double)ts.tv_nsec;
}

int cmp_by_colour_then_number(const void *a, const void *b){
    const Item *x=a, *y=b;
    if(x->colour!=y->colour) return x->colour-y->colour;
    return x->number-y->number;
}

int main(void){
    /* ---- small hand-checkable demo ---- */
    Item demo[] = {
        {1,RED},{3,YELLOW},{5,BLUE},{7,RED},{9,YELLOW},{12,BLUE},{15,RED}
    };
    int dn = sizeof(demo)/sizeof(demo[0]);
    Item *dout = malloc(dn*sizeof(Item));
    sort_by_colour(demo, dn, dout);
    printf("Demo input  (sorted by number): ");
    for(int i=0;i<dn;i++) printf("(%d,%s) ", demo[i].number, colour_name(demo[i].colour));
    printf("\nDemo output (grouped by colour): ");
    for(int i=0;i<dn;i++) printf("(%d,%s) ", dout[i].number, colour_name(dout[i].colour));
    printf("\nValid: %s\n\n", is_valid_result(dout,dn)? "YES":"NO");
    free(dout);

    /* ---- correctness + timing across sizes, comparing our O(n)
            algorithm against a baseline O(n log n) qsort by colour ---- */
    FILE *fp=fopen("results/q1_timings.csv","w");
    fprintf(fp,"n,on_algorithm_ns,qsort_baseline_ns\n");

    srand(1);
    int all_ok=1;
    int sizes[]={1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1000000};
    for(int s=0;s<11;s++){
        int n=sizes[s];
        Item *in=malloc(n*sizeof(Item));
        int cur=0;
        for(int i=0;i<n;i++){
            cur += 1+rand()%3;              /* strictly increasing numbers */
            in[i].number=cur;
            in[i].colour=(Colour)(rand()%3);
        }
        Item *out=malloc(n*sizeof(Item));

        double t0=now_ns();
        sort_by_colour(in,n,out);
        double t1=now_ns();
        if(!is_valid_result(out,n)){ all_ok=0; printf("FAIL at n=%d\n", n); }

        /* baseline: general-purpose O(n log n) comparison sort on a copy */
        Item *in2=malloc(n*sizeof(Item));
        memcpy(in2,in,n*sizeof(Item));
        double t2=now_ns();
        qsort(in2,n,sizeof(Item),cmp_by_colour_then_number);
        double t3=now_ns();

        fprintf(fp,"%d,%.0f,%.0f\n", n, t1-t0, t3-t2);
        printf("n=%8d  O(n) algorithm=%10.0f ns   qsort baseline=%10.0f ns\n", n, t1-t0, t3-t2);

        free(in); free(out); free(in2);
    }
    fclose(fp);
    printf(all_ok? "\nAll correctness checks PASSED.\n" : "\nSOME CHECKS FAILED.\n");
    printf("Wrote results/q1_timings.csv\n");
    return 0;
}
