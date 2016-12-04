
#include <stdio.h>
#include <vsip.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define M  42000
#define N  42000
#define P  3
#define L  1
#define alpha 2.0
#define beta  3.5

/* Testing vsip_gemp_f_para() */


int main(){vsip_init((void*)0);
{
    printf("Test vsip_gemp_f_para\n");

     int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
       printf("Number of threads = %d\n", nthreads);
   void VU_mfill_f(vsip_mview_f*, vsip_scalar_f);
   vsip_mview_f *A = vsip_mcreate_f(M,N,VSIP_ROW,0),
                *B = vsip_mcreate_f(P,M,VSIP_ROW,0),
                *C = vsip_mcreate_f(N,P,VSIP_ROW,0),
                *D = vsip_mcreate_f(N,P,VSIP_ROW,0);
   int row, col,i;
   for(row=0;row<M;row++) for(col=0;col<N;col++)
        vsip_mput_f(A,row,col,1 + sqrt(col*row));
   
   for(row=0;row<P;row++) for(col=0;col<M;col++)
        vsip_mput_f(B,row,col,1 + row * col);
   
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
         vsip_gemp_f(alpha,A,OpA,B,OpB,beta,C);
      }
      clock_t end_t = clock();
      double wall_timer_end = omp_get_wtime();
      printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

      start_t = clock();
      wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_gemp_f_para(alpha,A,OpA,B,OpB,beta,D);
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
     
/* expected output */
/* A input 
/ [
/ 1.0000  1.0000  1.0000 ;
/ 1.0000  2.0000  2.4142 ;
/ 1.0000  2.4142  3.0000 ;
/ 1.0000  2.7321  3.4495 ;
/ ];
/ 
/  B input 
/ [
/ 1.0000  1.0000  1.0000  1.0000  1.0000 ;
/ 1.0000  2.0000  3.0000  4.0000  5.0000 ;
/ 1.0000  3.0000  5.0000  7.0000  9.0000 ;
/ ];
/ alpha= 2.000000, beta= 3.500000,
/ OpA 0
/ C number 0
/ [
/ 6.0000  12.0000  18.0000  24.0000  30.0000 ;
/ 10.8284  24.4853  38.1421  51.7990  65.4558 ;
/ 12.8284  29.6569  46.4853  63.3137  80.1421 ;
/ 14.3631  33.6251  52.8872  72.1493  91.4113 ;
/ ];
/ C number 1
/ [
/ 27.0000  54.0000  81.0000  108.0000  135.0000 ;
/ 48.7279  110.1838  171.6396  233.0955  294.5513 ;
/ 57.7279  133.4558  209.1838  284.9117  360.6396 ;
/ 64.6339  151.3131  237.9924  324.6717  411.3510 ;
/ ];
/ C number 2
/ [
/ 100.5000  201.0000  301.5000  402.0000  502.5000 ;
/ 181.3762  410.1285  638.8807  867.6332  1096.3853 ;
/ 214.8762  496.7523  778.6285  1060.5046  1342.3806 ;
/ 240.5816  563.2211  885.8607  1208.5002  1531.1396 ;
/ ]; */
