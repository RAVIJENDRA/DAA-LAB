/*
DAA Lab-02, Q3: Merging k sorted arrays of n elements each.
Method 1: Sequential merge - O(nk^2)
Method 2: Pairwise/Tournament merge - O(nk log k)
Compile: gcc -O2 -o q3_merge_k_arrays q3_merge_k_arrays.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int*merge_two(int*a,int na,int*b,int nb){
int*out=malloc((na+nb)*sizeof(int));
int i=0,j=0,k=0;
while(i<na&&j<nb)
out[k++]=(a[i]<=b[j])?a[i++]:b[j++];
while(i<na)
out[k++]=a[i++];
while(j<nb)
out[k++]=b[j++];
return out;
}

int*method1(int**arrs,int k,int n,int*out_len){
int cur_len=n;
int*cur=malloc(n*sizeof(int));
memcpy(cur,arrs[0],n*sizeof(int));
for(int i=1;i<k;i++){
int*merged=merge_two(cur,cur_len,arrs[i],n);
free(cur);
cur=merged;
cur_len+=n;
}
*out_len=cur_len;
return cur;
}

int*method2(int**arrs,int k,int n,int*out_len){
int cnt=k;
int**cur=malloc(k*sizeof(int*));
int*lens=malloc(k*sizeof(int));
for(int i=0;i<k;i++){
cur[i]=malloc(n*sizeof(int));
memcpy(cur[i],arrs[i],n*sizeof(int));
lens[i]=n;
}
while(cnt>1){
int newcnt=(cnt+1)/2;
int**next=malloc(newcnt*sizeof(int*));
int*nlens=malloc(newcnt*sizeof(int));
int idx=0;
for(int i=0;i<cnt;i+=2){
if(i+1<cnt){
next[idx]=merge_two(cur[i],lens[i],cur[i+1],lens[i+1]);
nlens[idx]=lens[i]+lens[i+1];
free(cur[i]);
free(cur[i+1]);
}else{
next[idx]=cur[i];
nlens[idx]=lens[i];
}
idx++;
}
free(cur);
free(lens);
cur=next;
lens=nlens;
cnt=newcnt;
}
*out_len=lens[0];
int*result=cur[0];
free(cur);
free(lens);
return result;
}

double now_sec(void){
return(double)clock()/CLOCKS_PER_SEC;
}
int is_sorted(int*a,int n){
for(int i=1;i<n;i++)
if(a[i-1]>a[i])
return 0;
return 1;
}
int cmp(const void*a,const void*b){
int x=*(const int*)a;
int y=*(const int*)b;
if(x<y)return-1;
if(x>y)return 1;
return 0;
}
int**make_arrays(int k,int n,unsigned seed){
srand(seed);
int**arrs=malloc(k*sizeof(int*));
for(int i=0;i<k;i++){
arrs[i]=malloc(n*sizeof(int));
for(int j=0;j<n;j++)
arrs[i][j]=rand()%1000000;
qsort(arrs[i],n,sizeof(int),cmp);
}
return arrs;
}
void free_arrays(int**arrs,int k){
for(int i=0;i<k;i++)
free(arrs[i]);
free(arrs);
}

int main(void){
FILE*fp=fopen("q3_timings.csv","w");
if(fp==NULL){
printf("Error opening q3_timings.csv\n");
return 1;
}
fprintf(fp,"experiment,n,k,method1_time,method2_time\n");

int n_fixed=500;
int ks[]={2,4,8,16,32,64,128,256,512};
int nk=sizeof(ks)/sizeof(ks[0]);

for(int idx=0;idx<nk;idx++){
int k=ks[idx];
printf("Running Experiment A: n=%d,k=%d\n",n_fixed,k);
int**arrs=make_arrays(k,n_fixed,123);
int len1,len2;
double t0=now_sec();
int*r1=method1(arrs,k,n_fixed,&len1);
double t1=now_sec();
double t2=now_sec();
int*r2=method2(arrs,k,n_fixed,&len2);
double t3=now_sec();
if(!is_sorted(r1,len1)||!is_sorted(r2,len2)||len1!=len2)
printf("ERROR at k=%d\n",k);
fprintf(fp,"vary_k,%d,%d,%.6f,%.6f\n",n_fixed,k,t1-t0,t3-t2);
printf("Method 1: %.6f seconds\n",t1-t0);
printf("Method 2: %.6f seconds\n\n",t1-t0);
free(r1);
free(r2);
free_arrays(arrs,k);
}

int k_fixed=16;
int ns[]={500,1000,2000,4000,8000,16000,32000,64000};
int nn=sizeof(ns)/sizeof(ns[0]);

for(int idx=0;idx<nn;idx++){
int n=ns[idx];
printf("Running Experiment B: n=%d,k=%d\n",n,k_fixed);
int**arrs=make_arrays(k_fixed,n,456);
int len1,len2;
double t0=now_sec();
int*r1=method1(arrs,k_fixed,n,&len1);
double t1=now_sec();
double t2=now_sec();
int*r2=method2(arrs,k_fixed,n,&len2);
double t3=now_sec();
if(!is_sorted(r1,len1)||!is_sorted(r2,len2)||len1!=len2)
printf("ERROR at n=%d\n",n);
fprintf(fp,"vary_n,%d,%d,%.6f,%.6f\n",n,k_fixed,t1-t0,t2-t1);
printf("Method 1: %.6f seconds\n",t1-t0);
printf("Method 2: %.6f seconds\n\n",t3-t2);
free(r1);
free(r2);
free_arrays(arrs,k_fixed);
}
fclose(fp);
printf("Experiment completed successfully.\n");
printf("Output file: q3_timings.csv\n");
return 0;
}
