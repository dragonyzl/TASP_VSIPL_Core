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

#define N  1000000
#define L  200

int main(){vsip_init((void*)0);
{
   void VU_vprint_f(vsip_vview_f*);
   vsip_vview_f *A = vsip_vcreate_f(N,0);
   vsip_vview_f *B = vsip_vcreate_f(N,0);
   vsip_vview_f *C = vsip_vcreate_f(N,0);
   vsip_vramp_f(0,1,A);
   printf("A = \n");VU_vprint_f(A);

   vsip_vfill_f(2.5,B);
   printf("B = \n");VU_vprint_f(B);
   vsip_vcopy_f_f_para(A,B);
    printf("after copy B = \n");VU_vprint_f(B);

   vsip_scalar_f sum = vsip_vsumval_f_para(A);
   printf("sum para of vect = %.2f\n\n", sum);

   vsip_scalar_f sqsumpara = vsip_vsumsqval_f_para(A);
   printf("square sum para of vect = %.2f\n\n", sqsumpara);

   vsip_scalar_f dotpara = vsip_vdot_f_para(A,B);
   printf("dot AB para of vect = %.2f\n\n", dotpara);

   vsip_vmul_f_para(A,B,C);
   printf("C = \n");VU_vprint_f(C);

int i;
      clock_t start_t = clock();
      for(i=0; i<L; i++){
          dotpara=vsip_vdot_f(A,B);
      }
      clock_t end_t = clock();
      printf("omp_get_wtime(): %f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

      start_t = clock();
      for(i=0; i<L; i++){
          dotpara=vsip_vdot_f_para(A,B);
      }
      end_t = clock();
      printf("omp_get_wtime(): %f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

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
