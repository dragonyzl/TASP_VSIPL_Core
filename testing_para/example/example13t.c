/* Created RJudd */
/* SPAWARSYSCEN D881 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id$ */


#include<stdio.h>
#include<vsip.h>
#include <omp.h>
#include <time.h>


int main(int argc, char *argv[]){vsip_init((void*)0);
{
    printf("Test vsip_vmul_f_para\n");

int L,N;
if(argc < 2){
      printf("usage\nqrdex N L\n");
      printf("defaule N 1000000000 L 5\n");
      N = 1000000000;
      L = 5;
   }
 else {
                  N    = (vsip_length)atoi(argv[1]);
                  L    = (vsip_length)atoi(argv[2]);
 }


     int nthreads;
 #pragma omp parallel
   {
     nthreads = omp_get_num_threads();
   }
       printf("Number of threads = %d\n", nthreads);

   void VU_vprint_f(vsip_vview_f*);
   vsip_vview_f *A = vsip_vcreate_f(N,0);
   vsip_vview_f *B = vsip_vcreate_f(N,0);
   vsip_vview_f *C = vsip_vcreate_f(N,0);
   vsip_vramp_f(0,1,A);

   vsip_vfill_f(2.5,B);


int i;
      clock_t start_t = clock();
      double wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         vsip_vmul_f(A,B,C);
      }
      clock_t end_t = clock();
      double wall_timer_end = omp_get_wtime();
      printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

      start_t = clock();
      wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
          vsip_vmul_f_para(A,B,C);
      }
      end_t = clock();
      wall_timer_end = omp_get_wtime();
      printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\nNUM_THREADS = %d\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start,nthreads);

   vsip_valldestroy_f(A);
   vsip_valldestroy_f(B);
   vsip_valldestroy_f(C);
} vsip_finalize((void*)0); 
   return 1;
}

void VU_vprint_f(vsip_vview_f* a){
   vsip_length i;
   for(i=0; i<vsip_vgetlength_f(a); i++)
   printf("%4.0f",vsip_vget_f(a,i));
   printf("\n");
   return;
}
