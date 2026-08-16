/* ============================================================
   Q4: Strassen's Matrix Multiplication (Divide and Conquer)
   ------------------------------------------------------------
   Naive multiply:  O(n^3)
   Strassen:         7 recursive multiplications of (n/2)x(n/2)
                     submatrices instead of the natural 8, using:

     A = [[A11,A12],[A21,A22]], B = [[B11,B12],[B21,B22]]

     M1 = (A11+A22)(B11+B22)
     M2 = (A21+A22) B11
     M3 = A11 (B12-B22)
     M4 = A22 (B21-B11)
     M5 = (A11+A12) B22
     M6 = (A21-A11) (B11+B12)
     M7 = (A12-A22) (B21+B22)

     C11 = M1+M4-M5+M7
     C12 = M3+M5
     C21 = M2+M4
     C22 = M1-M2+M3+M6

   T(n) = 7T(n/2) + O(n^2)  ->  Theta(n^log2 7) = Theta(n^2.807)
   which beats naive Theta(n^3) for large n.

   This program pads to the next power of 2, runs both algorithms
   on random matrices, checks they agree, and times both to
   validate the complexity difference.
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

ll** alloc_mat(int n){
    ll **m=malloc(n*sizeof(ll*));
    for(int i=0;i<n;i++) m[i]=calloc(n,sizeof(ll));
    return m;
}
void free_mat(ll **m,int n){ for(int i=0;i<n;i++) free(m[i]); free(m); }

void add(ll **A, ll **B, ll **C, int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]+B[i][j]; }
void sub(ll **A, ll **B, ll **C, int n){ for(int i=0;i<n;i++) for(int j=0;j<n;j++) C[i][j]=A[i][j]-B[i][j]; }

/* ---------------- naive O(n^3) ---------------- */
void naive_multiply(ll **A, ll **B, ll **C, int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            ll s=0;
            for(int k=0;k<n;k++) s+=A[i][k]*B[k][j];
            C[i][j]=s;
        }
}

/* ---------------- Strassen ---------------- */
void strassen(ll **A, ll **B, ll **C, int n){
    if(n<=64){ naive_multiply(A,B,C,n); return; } /* base case: naive is faster for small n */
    int h=n/2;
    ll **A11=alloc_mat(h),**A12=alloc_mat(h),**A21=alloc_mat(h),**A22=alloc_mat(h);
    ll **B11=alloc_mat(h),**B12=alloc_mat(h),**B21=alloc_mat(h),**B22=alloc_mat(h);
    for(int i=0;i<h;i++) for(int j=0;j<h;j++){
        A11[i][j]=A[i][j];       A12[i][j]=A[i][j+h];
        A21[i][j]=A[i+h][j];     A22[i][j]=A[i+h][j+h];
        B11[i][j]=B[i][j];       B12[i][j]=B[i][j+h];
        B21[i][j]=B[i+h][j];     B22[i][j]=B[i+h][j+h];
    }
    ll **T1=alloc_mat(h),**T2=alloc_mat(h);
    ll **M1=alloc_mat(h),**M2=alloc_mat(h),**M3=alloc_mat(h),**M4=alloc_mat(h),
       **M5=alloc_mat(h),**M6=alloc_mat(h),**M7=alloc_mat(h);

    add(A11,A22,T1,h); add(B11,B22,T2,h); strassen(T1,T2,M1,h);
    add(A21,A22,T1,h); strassen(T1,B11,M2,h);
    sub(B12,B22,T2,h); strassen(A11,T2,M3,h);
    sub(B21,B11,T2,h); strassen(A22,T2,M4,h);
    add(A11,A12,T1,h); strassen(T1,B22,M5,h);
    sub(A21,A11,T1,h); add(B11,B12,T2,h); strassen(T1,T2,M6,h);
    sub(A12,A22,T1,h); add(B21,B22,T2,h); strassen(T1,T2,M7,h);

    for(int i=0;i<h;i++) for(int j=0;j<h;j++){
        C[i][j]     = M1[i][j]+M4[i][j]-M5[i][j]+M7[i][j];
        C[i][j+h]   = M3[i][j]+M5[i][j];
        C[i+h][j]   = M2[i][j]+M4[i][j];
        C[i+h][j+h] = M1[i][j]-M2[i][j]+M3[i][j]+M6[i][j];
    }

    free_mat(A11,h);free_mat(A12,h);free_mat(A21,h);free_mat(A22,h);
    free_mat(B11,h);free_mat(B12,h);free_mat(B21,h);free_mat(B22,h);
    free_mat(T1,h);free_mat(T2,h);
    free_mat(M1,h);free_mat(M2,h);free_mat(M3,h);free_mat(M4,h);
    free_mat(M5,h);free_mat(M6,h);free_mat(M7,h);
}

ll** random_mat(int n, unsigned seed){
    ll **m=alloc_mat(n);
    srand(seed);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) m[i][j]=rand()%10;
    return m;
}
int equal_mat(ll **A, ll **B, int n){
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(A[i][j]!=B[i][j]) return 0;
    return 1;
}

int main(void){
    FILE *fp=fopen("results/q4_timings.csv","w");
    fprintf(fp,"n,naive_ns,strassen_ns\n");

    /* correctness check on a modest size first */
    {
        int n=128;
        ll **A=random_mat(n,1), **B=random_mat(n,2);
        ll **C1=alloc_mat(n), **C2=alloc_mat(n);
        naive_multiply(A,B,C1,n);
        strassen(A,B,C2,n);
        printf("Correctness check (n=%d): %s\n", n, equal_mat(C1,C2,n)? "PASSED":"FAILED");
        free_mat(A,n);free_mat(B,n);free_mat(C1,n);free_mat(C2,n);
    }

    int sizes[]={32,64,128,256,512,1024};
    for(int s=0;s<6;s++){
        int n=sizes[s];
        ll **A=random_mat(n,10+s), **B=random_mat(n,20+s), **C=alloc_mat(n);

        double t0=now_ns(); naive_multiply(A,B,C,n); double t1=now_ns();
        double t2=now_ns(); strassen(A,B,C,n); double t3=now_ns();

        fprintf(fp,"%d,%.0f,%.0f\n", n, t1-t0, t3-t2);
        printf("n=%5d  naive=%12.0f ns   strassen=%12.0f ns\n", n, t1-t0, t3-t2);

        free_mat(A,n);free_mat(B,n);free_mat(C,n);
    }
    fclose(fp);
    printf("Wrote results/q4_timings.csv\n");
    return 0;
}
