/* ============================================================
   Q5: Multiply special-pattern matrices  M = [[M1,M2],[M2,M1]]  in O(n^2)
   ------------------------------------------------------------
   KEY FACT: this "2-fold circulant" block pattern is CLOSED under
   matrix addition and (as we prove below) under matrix multiplication.
   That closure is exactly what lets us recurse.

   Let M = [[M1,M2],[M2,M1]], N = [[N1,N2],[N2,N1]]. Block-multiplying:
       P11 = M1N1 + M2N2         P12 = M1N2 + M2N1
       P21 = M2N1 + M1N2 = P12   P22 = M2N2 + M1N1 = P11
   So P is ALSO of the pattern [[P11,P12],[P12,P11]] -- we only ever
   need to compute P11 and P12, i.e. only track an (M1,M2) pair at
   every level, never a full redundant matrix.

   Naively P11, P12 need 4 sub-multiplications (M1N1, M2N2, M1N2, M2N1)
   which gives T(n) = 4T(n/2) + O(n^2) = O(n^2 log n) -- NOT good enough.

   TRICK (same idea as Karatsuba, applied to this 2x2 "ring"):
       Let S = M1+M2, D = M1-M2, S' = N1+N2, D' = N1-N2.
       S*S' = M1N1 + M1N2 + M2N1 + M2N2 = P11 + P12
       D*D' = M1N1 - M1N2 - M2N1 + M2N2 = P11 - P12
       =>  P11 = (S*S' + D*D') / 2      P12 = (S*S' - D*D') / 2

   S, D (and S', D') are themselves circulant-block matrices of half
   the size (sums/differences of circulant matrices are circulant),
   so S*S' and D*D' can be computed with the SAME algorithm, recursively.
   Only 2 recursive multiplications per level now:

       T(n) = 2*T(n/2) + O(n^2)   -- Master theorem case 3 -->  T(n) = O(n^2)

   Base case: n=1 (M1,M2 are scalars) -- direct formula, O(1).
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ll;

static double now_ns(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec*1e9 + (double)ts.tv_nsec;
}

ll** alloc_mat(int n){ ll **m=malloc(n*sizeof(ll*)); for(int i=0;i<n;i++) m[i]=calloc(n,sizeof(ll)); return m; }
void free_mat(ll **m,int n){ for(int i=0;i<n;i++) free(m[i]); free(m); }
void madd(ll**A,ll**B,ll**C,int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]+B[i][j]; }
void msub(ll**A,ll**B,ll**C,int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]-B[i][j]; }
void mcopy(ll**A,ll**C,int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]; }

/* Multiplies two circulant-patterned matrices, each represented by
   its top blocks M1,M2 (both size x size). Produces the result's
   top blocks P1,P2 (P1=P11, P2=P12; caller knows P21=P2, P22=P1). */
void circMul(int size, ll **M1, ll **M2, ll **N1, ll **N2, ll **P1, ll **P2){
    if(size==1){
        ll s=M1[0][0]+M2[0][0], d=M1[0][0]-M2[0][0];
        ll sp=N1[0][0]+N2[0][0], dp=N1[0][0]-N2[0][0];
        ll ss=s*sp, dd=d*dp;
        P1[0][0]=(ss+dd)/2;
        P2[0][0]=(ss-dd)/2;
        return;
    }
    ll **S=alloc_mat(size), **D=alloc_mat(size), **Sp=alloc_mat(size), **Dp=alloc_mat(size);
    madd(M1,M2,S,size); msub(M1,M2,D,size);
    madd(N1,N2,Sp,size); msub(N1,N2,Dp,size);

    /* S,D,Sp,Dp are (size x size) circulant matrices in their own right;
       split each into ITS top blocks to recurse at size/2 */
    int h=size/2;
    ll **Sa=alloc_mat(h),**Sb=alloc_mat(h),**Da=alloc_mat(h),**Db=alloc_mat(h);
    ll **Spa=alloc_mat(h),**Spb=alloc_mat(h),**Dpa=alloc_mat(h),**Dpb=alloc_mat(h);
    for(int i=0;i<h;i++) for(int j=0;j<h;j++){
        Sa[i][j]=S[i][j]; Sb[i][j]=S[i][j+h];
        Da[i][j]=D[i][j]; Db[i][j]=D[i][j+h];
        Spa[i][j]=Sp[i][j]; Spb[i][j]=Sp[i][j+h];
        Dpa[i][j]=Dp[i][j]; Dpb[i][j]=Dp[i][j+h];
    }
    ll **SSa=alloc_mat(h), **SSb=alloc_mat(h), **DDa=alloc_mat(h), **DDb=alloc_mat(h);
    circMul(h, Sa,Sb, Spa,Spb, SSa,SSb);   /* recursive: S*S'  (recurse one level, size/2) */
    circMul(h, Da,Db, Dpa,Dpb, DDa,DDb);   /* recursive: D*D'  */

    /* S*S' and D*D' are each (size x size) circulant matrices;
       reassemble their FULL size x size form from (SSa,SSb)/(DDa,DDb),
       then combine: P1=(SS+DD)/2, P2=(SS-DD)/2 */
    for(int i=0;i<h;i++) for(int j=0;j<h;j++){
        ll ss11=SSa[i][j], ss12=SSb[i][j];
        ll dd11=DDa[i][j], dd12=DDb[i][j];
        P1[i][j]       = (ss11+dd11)/2;   P1[i][j+h]     = (ss12+dd12)/2;
        P1[i+h][j]     = (ss12+dd12)/2;   P1[i+h][j+h]   = (ss11+dd11)/2;
        P2[i][j]       = (ss11-dd11)/2;   P2[i][j+h]     = (ss12-dd12)/2;
        P2[i+h][j]     = (ss12-dd12)/2;   P2[i+h][j+h]   = (ss11-dd11)/2;
    }

    free_mat(S,size);free_mat(D,size);free_mat(Sp,size);free_mat(Dp,size);
    free_mat(Sa,h);free_mat(Sb,h);free_mat(Da,h);free_mat(Db,h);
    free_mat(Spa,h);free_mat(Spb,h);free_mat(Dpa,h);free_mat(Dpb,h);
    free_mat(SSa,h);free_mat(SSb,h);free_mat(DDa,h);free_mat(DDb,h);
}

/* naive O(n^3) full multiply, used only to validate correctness */
void naive_multiply(ll **A, ll **B, ll **C, int n){
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        ll s=0; for(int k=0;k<n;k++) s+=A[i][k]*B[k][j];
        C[i][j]=s;
    }
}

/* Recursively enforces the circulant block pattern within X, starting
   at offset (row,col), for an s x s sub-region: fixes the top-left (M1)
   and top-right (M2) quadrants FIRST (all the way down to scalars),
   then mirrors them into the bottom-left/bottom-right quadrants. */
void enforce_pattern(ll **X, int row, int col, int s){
    if(s==1) return;
    int h=s/2;
    enforce_pattern(X, row,   col,   h);  /* fix M1 fully */
    enforce_pattern(X, row,   col+h, h);  /* fix M2 fully */
    for(int i=0;i<h;i++) for(int j=0;j<h;j++){
        X[row+h+i][col+j]   = X[row+i][col+h+j]; /* bottom-left  = M2 */
        X[row+h+i][col+h+j] = X[row+i][col+j];   /* bottom-right = M1 */
    }
}

/* builds a random circulant-patterned NxN matrix (N=2*size) and
   returns it both as a full matrix and as its (M1,M2) block pair */
void make_random_circulant(int size, ll ***outM1, ll ***outM2, ll ***outFull, unsigned seed){
    srand(seed);
    ll **M1=alloc_mat(size), **M2=alloc_mat(size);
    for(int i=0;i<size;i++) for(int j=0;j<size;j++){ M1[i][j]=rand()%10; M2[i][j]=rand()%10; }
    enforce_pattern(M1, 0, 0, size);
    enforce_pattern(M2, 0, 0, size);

    int N=2*size;
    ll **full=alloc_mat(N);
    for(int i=0;i<size;i++) for(int j=0;j<size;j++){
        full[i][j]=M1[i][j];           full[i][j+size]=M2[i][j];
        full[i+size][j]=M2[i][j];      full[i+size][j+size]=M1[i][j];
    }
    *outM1=M1; *outM2=M2; *outFull=full;
}

int equal_mat(ll**A,ll**B,int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(A[i][j]!=B[i][j]) return 0; return 1; }

int main(void){
    FILE *fp=fopen("results/q5_timings.csv","w");
    fprintf(fp,"n,naive_ns,special_ns\n");

    /* correctness check */
    {
        int size=32; /* block size -> full matrix is 64x64 */
        ll **M1,**M2,**Mfull,**N1,**N2,**Nfull;
        make_random_circulant(size,&M1,&M2,&Mfull,11);
        make_random_circulant(size,&N1,&N2,&Nfull,22);

        int N=2*size;
        ll **Cnaive=alloc_mat(N);
        naive_multiply(Mfull,Nfull,Cnaive,N);

        ll **P1=alloc_mat(size), **P2=alloc_mat(size);
        circMul(size,M1,M2,N1,N2,P1,P2);
        ll **Cspecial=alloc_mat(N);
        for(int i=0;i<size;i++) for(int j=0;j<size;j++){
            Cspecial[i][j]=P1[i][j];             Cspecial[i][j+size]=P2[i][j];
            Cspecial[i+size][j]=P2[i][j];        Cspecial[i+size][j+size]=P1[i][j];
        }
        printf("Correctness check (N=%d): %s\n", N, equal_mat(Cnaive,Cspecial,N)? "PASSED":"FAILED");
        free_mat(M1,size);free_mat(M2,size);free_mat(Mfull,N);
        free_mat(N1,size);free_mat(N2,size);free_mat(Nfull,N);
        free_mat(Cnaive,N);free_mat(P1,size);free_mat(P2,size);free_mat(Cspecial,N);
    }

    int sizes[]={16,32,64,128,256,512}; /* block sizes -> full matrix N=2*size */
    for(int s=0;s<6;s++){
        int size=sizes[s], N=2*size;
        ll **M1,**M2,**Mfull,**N1,**N2,**Nfull;
        make_random_circulant(size,&M1,&M2,&Mfull,100+s);
        make_random_circulant(size,&N1,&N2,&Nfull,200+s);
        ll **Cnaive=alloc_mat(N);
        ll **P1=alloc_mat(size), **P2=alloc_mat(size);

        double t0=now_ns(); naive_multiply(Mfull,Nfull,Cnaive,N); double t1=now_ns();
        double t2=now_ns(); circMul(size,M1,M2,N1,N2,P1,P2); double t3=now_ns();

        fprintf(fp,"%d,%.0f,%.0f\n", N, t1-t0, t3-t2);
        printf("N=%5d  naive(O(n^3))=%12.0f ns   special(O(n^2))=%12.0f ns\n", N, t1-t0, t3-t2);

        free_mat(M1,size);free_mat(M2,size);free_mat(Mfull,N);
        free_mat(N1,size);free_mat(N2,size);free_mat(Nfull,N);
        free_mat(Cnaive,N);free_mat(P1,size);free_mat(P2,size);
    }
    fclose(fp);
    printf("Wrote results/q5_timings.csv\n");
    return 0;
}
