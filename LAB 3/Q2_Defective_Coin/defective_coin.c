/* ============================================================
   Q2: Search the Defective (lighter) coin among n coins, using a
   balance scale, in log2(n) + c weighings, or report none defective.

   KEY IDEA:
   Because the defective coin (if it exists) is known to be LIGHTER
   (never heavier) and there is AT MOST ONE such coin, we don't need
   the classic base-3 "which of 3 groups" search used when the fake
   coin's direction is unknown. Instead:

       Split the current suspect set into two equal halves L, R
       (set aside one leftover coin if the count is odd) and put
       ALL of L in one pan, ALL of R in the other (one weighing
       compares the TOTAL weight of each pan):

         - balanced   -> L and R are BOTH fully genuine (a single
                          lighter coin among equal counts would have
                          tipped the scale). The defective, if it
                          exists at all, must be the leftover coin.
         - unbalanced -> the LIGHTER pan contains the defective coin
                          (the heavier pan is proven 100% genuine).
                          Recurse into the lighter pan ONLY.

   Each weighing halves the suspect set -> T(n) = T(n/2) + O(1)
                                          -> O(log2 n) weighings,
   plus at most 2 extra weighings for odd-size leftovers and the
   final single-coin confirmation -> log2(n) + c.
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double *coins;      /* global weight array for this run */
long weighings;     /* counts number of balance-scale operations used */

/* Simulates ONE use of the balance scale: compares total weight of
   coins[Llo..Lhi] against coins[Rlo..Rhi] (equal counts required).
   Returns -1 if L lighter, 0 if balanced, +1 if R lighter. */
int weigh(int Llo,int Lhi,int Rlo,int Rhi){
    weighings++;
    double sl=0, sr=0;
    for(int i=Llo;i<=Lhi;i++) sl+=coins[i];
    for(int i=Rlo;i<=Rhi;i++) sr+=coins[i];
    if(sl<sr-1e-9) return -1;
    if(sr<sl-1e-9) return 1;
    return 0;
}

/* weighs a single suspect coin against a single known-genuine coin */
int weighSingle(int suspect,int genuine){
    weighings++;
    if(coins[suspect]<coins[genuine]-1e-9) return -1; /* suspect lighter */
    return 0;
}

/* returns index of the defective coin in [lo,hi], or -1 if none.
   `ref` = index of a coin already known to be genuine, or -1 if
   none has been established yet (only true for the very first call). */
int findDefective(int lo,int hi,int ref){
    int n=hi-lo+1;
    if(n<=0) return -1;
    if(n==1){
        if(ref==-1) return -1; /* can't tell without a reference (won't happen for n>=2 top calls) */
        return (weighSingle(lo,ref)==-1) ? lo : -1;
    }
    int hasLeftover = (n%2==1);
    int leftover = hasLeftover ? hi : -1;
    int effHi = hasLeftover ? hi-1 : hi;
    int Lsize = (effHi-lo+1)/2;
    int Llo=lo, Lhi=lo+Lsize-1;
    int Rlo=Lhi+1, Rhi=effHi;

    int cmp = weigh(Llo,Lhi,Rlo,Rhi);
    if(cmp==0){                          /* both halves fully genuine */
        if(hasLeftover) return findDefective(leftover,leftover,Llo); /* Llo is a proven-genuine reference */
        return -1;
    } else if(cmp<0){                    /* L is lighter -> defective is in L */
        return findDefective(Llo,Lhi,Rlo);   /* R is proven genuine -> usable as reference */
    } else {                             /* R is lighter -> defective is in R */
        return findDefective(Rlo,Rhi,Llo);
    }
}

/* ---------------- test harness / validation ---------------- */
int run_trial(int n, int defectiveIdx /* -1 = no defect */){
    coins=malloc(n*sizeof(double));
    for(int i=0;i<n;i++) coins[i]=100.0;
    if(defectiveIdx>=0) coins[defectiveIdx]=99.0; /* lighter */
    weighings=0;
    int found = findDefective(0,n-1,-1);
    int ok = (found==defectiveIdx);
    free(coins);
    return ok ? (int)weighings : -1;
}

int main(void){
    FILE *fp=fopen("results/q2_weighings.csv","w");
    fprintf(fp,"n,max_weighings,theory_log2n\n");

    int all_ok=1;
    for(int n=2;n<=100000; n = (n<20)? n+1 : n*2){
        int worst=0;
        /* try every possible defect position + the "no defect" case, keep the worst */
        int positions_to_test = (n<=2000)? n : 200; /* sample for huge n to keep it fast */
        for(int p=-1; p<positions_to_test; p++){
            int idx = (p==-1)? -1 : (p * (n/positions_to_test==0?1:n/positions_to_test)) % n;
            int w = run_trial(n, idx);
            if(w<0){ all_ok=0; printf("MISMATCH at n=%d pos=%d\n", n, idx); }
            else if(w>worst) worst=w;
        }
        double theory=log2((double)n);
        fprintf(fp,"%d,%d,%.2f\n", n, worst, theory);
        printf("n=%7d  worst-case weighings=%3d   log2(n)=%.2f\n", n, worst, theory);
        if(n>=100000) break;
    }
    fclose(fp);
    printf(all_ok? "\nAll trials correctly identified the defective coin (or correctly reported none).\n"
                  : "\nSOME TRIALS FAILED -- see MISMATCH lines above.\n");
    printf("Wrote results/q2_weighings.csv\n");
    return 0;
}
