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

#define N  1000000000
#define L  5

int main(){vsip_init((void*)0);
{
   void VU_vprint_f(vsip_vview_f*);
   vsip_vview_f *A = vsip_vcreate_f(N,0);
   vsip_vview_f *B = vsip_vcreate_f(N,0);
   vsip_vview_f *C = vsip_vcreate_f(N,0);
   vsip_vramp_f(0,1,A);

   vsip_vfill_f(2.5,B);

   vsip_vcopy_f_f_para(A,B);

   vsip_scalar_f sum = vsip_vsumval_f_para(A);

   vsip_scalar_f sqsumpara = vsip_vsumsqval_f_para(A);

   vsip_scalar_f dotpara = vsip_vdot_f_para(A,B);

   vsip_vmul_f_para(A,B,C);

int i;
      clock_t start_t = clock();
      double wall_timer_start = omp_get_wtime();
      for(i=0; i<L; i++){
         sqsumpara = vsip_vsumsqval_f(A);
      }
      clock_t end_t = clock();
      double wall_timer_end = omp_get_wtime();
      printf("before para CPU total clock(): %f\nwall time omp_get_wtime():%f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

      start_t = clock();
      wall_timer_start = omp_get_wtime();
#pragma omp parallel for
      for(i=0; i<L; i++){
          sqsumpara = vsip_vsumsqval_f_para(A);
      }
      end_t = clock();
      wall_timer_end = omp_get_wtime();
      printf("after para CPU total clock(): %f\nwall time omp_get_wtime():%f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC,wall_timer_end-wall_timer_start);

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
