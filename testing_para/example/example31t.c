
#include <stdio.h>
#include <vsip.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define alpha 2.0
#define beta  3.5

/* Testing vsip_gemp_f_para() */


int main(int argc, char *argv[]){vsip_init((void*)0);
{
    printf("Test vsip_gems_f_para\n");

      vsip_length M,N,P,L;

if(argc < 3){
      printf("usage\nqrdex M N P L\n");
      printf("defaule M42000 N42000 L1\n");
      M = 42000;
      N = 42000;
      L = 1;
   }
 else {
                  M    = (vsip_length)atoi(argv[1]);
                  N    = (vsip_length)atoi(argv[2]);
                  L    = (vsip_length)atoi(argv[3]);
 }
     int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
       printf("Number of threads = %d\n", nthreads);
   void VU_mfill_f(vsip_mview_f*, vsip_scalar_f);
   vsip_mview_f *A = vsip_mcreate_f(N,M,VSIP_ROW,0),
                *B = vsip_mcreate_f(N,M,VSIP_ROW,0),
                *C = vsip_mcreate_f(N,M,VSIP_ROW,0),
                *D = vsip_mcreate_f(N,M,VSIP_ROW,0);
   int row, col,i;
   for(row=0;row<N;row++) for(col=0;col<M;col++)
        vsip_mput_f(A,row,col,1 + sqrt(col*row));
   
   for(row=0;row<N;row++) for(col=0;col<M;col++)
        vsip_mput_f(B,row,col,1 + sqrt(col*row));

   VU_mfill_f(C,0);
   VU_mfill_f(D,0);


   {
      vsip_mat_op OpA = VSIP_MAT_TRANS;
      vsip_mat_op OpB = VSIP_MAT_TRANS;

      /*printf("OpA %i\n",OpA);*/
      
      printf("matrix size: %d*%d, calc %d times\n",M,N,L);
      clock_t start_t = clock();
      double wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_gems_f(alpha,A,OpA,beta,C);
      }
      clock_t end_t = clock();
      double wall_timer_end = omp_get_wtime();
      printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

      start_t = clock();
      wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_gems_f_para(alpha,B,OpB,beta,D);
      }
      end_t = clock();
      wall_timer_end = omp_get_wtime();
      printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);

   }
   vsip_malldestroy_f(A);
   vsip_malldestroy_f(B);
   vsip_malldestroy_f(C);
   vsip_malldestroy_f(D);

   } vsip_finalize((void*)0); return 0;
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
     