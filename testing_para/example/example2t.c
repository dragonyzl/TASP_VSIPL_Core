
#include <stdio.h>
#include<vsip.h>
#include <omp.h>
#include <time.h>

/*Testing vsip_gems_f_para()*/

#define M  42000
#define N  42000
#define L  1
#define alpha 2.0
#define beta  3.5

int main(){vsip_init((void*)0);
{
    printf("Test vsip_gems_f_para\n");
     int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
       printf("Number of threads = %d\n", nthreads);

   void VU_mprint_f(vsip_mview_f*);
   void VU_mfill_f(vsip_mview_f*, vsip_scalar_f);
   vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_ROW,0),
                *C = vsip_mcreate_f(N,M,VSIP_ROW,0),
                *D = vsip_mcreate_f(N,M,VSIP_ROW,0);
   int row, col,i;
   for(row=0;row<M;row++) for(col=0;col<N;col++)
        vsip_mput_f(A,row,col,1 + sqrt(col*row));
   
   VU_mfill_f(C,0);
   VU_mfill_f(D,0);
   
   printf("alpha= %f, beta= %f,\n",alpha,beta);
   {
      vsip_mat_op OpA = VSIP_MAT_TRANS;
      /*vsip_mat_op OpA = VSIP_MAT_NTRANS;*/
      
      clock_t start_t = clock();
      double wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_gems_f(alpha,A,OpA,beta,C);
         
      }
      clock_t end_t = clock();
      double wall_timer_end = omp_get_wtime();
      printf("before para CPU total clock(): %f\nwall time:%f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

      start_t = clock();
      wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_gems_f_para(alpha,A,OpA,beta,D);
         
      }
      end_t = clock();
      wall_timer_end = omp_get_wtime();
      printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);

   }
   vsip_malldestroy_f(A);
   vsip_malldestroy_f(C);
   vsip_malldestroy_f(D);
   } vsip_finalize((void*)0); return 0;
}
void VU_mprint_f(vsip_mview_f *X)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    vsip_scalar_f x;
    printf("[\n");
    for(row=0; row<CL; row++){
      for(col=0; col<RL; col++){
        x=vsip_mget_f(X,row,col);
        printf("%6.4f %s",x,((col==(RL-1)) ? ";" : " "));
      }  
      printf("\n");
    }
    printf("];\n");
    return;
}
void VU_mfill_f(vsip_mview_f *X, vsip_scalar_f a)
{
    vsip_length RL = vsip_mgetrowlength_f(X);
    vsip_length CL = vsip_mgetcollength_f(X);
    vsip_length row,col;
    for(row=0; row<CL; row++)
      for(col=0; col<RL; col++)
        vsip_mput_f(X,row,col,a);
    return;
}
     
/* expected output */
