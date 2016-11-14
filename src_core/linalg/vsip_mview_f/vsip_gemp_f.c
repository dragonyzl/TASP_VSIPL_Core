/* Created RJudd January 27, 1999 */
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
/* $Id: vsip_gemp_f.c,v 1.2 1999/12/02 18:43:15 judd Exp judd $ */
/* vsip_gemp_f */
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip.h>
#include<VI_functions_f.h>

void (vsip_gemp_f)(vsip_scalar_f alpha,
                   const vsip_mview_f *AA,
                   vsip_mat_op OpA,
                   const vsip_mview_f *BB,
                   vsip_mat_op OpB,
                   vsip_scalar_f beta,
                   const vsip_mview_f *C){
vsip_mview_f At = *AA,
             Bt = *BB;
vsip_mview_f *A = &At,
             *B = &Bt;
if(OpA == 1){
     A->row_length = AA->col_length;
     A->col_length = AA->row_length;
     A->row_stride = AA->col_stride;
     A->col_stride = AA->row_stride;
}
if(OpB == 1){
     B->row_length = BB->col_length;
     B->col_length = BB->row_length;
     B->row_stride = BB->col_stride;
     B->col_stride = BB->row_stride;
}
{
    vsip_length M = A->col_length,
                N = B->row_length;
    vsip_length i,j;
    vsip_vview_f aa,bb,cc;
    vsip_vview_f *a = VI_mrowview_f(A,0,&aa),
                 *b = VI_mcolview_f(B,0,&bb),
                 *c = VI_mrowview_f(C,0,&cc);
    {
      vsip_stride str  = c->stride * c->block->rstride;
      vsip_stride str1 = C->col_stride * C->block->rstride;
      vsip_scalar_f  *c_pr =(vsip_scalar_f*) (c->block->array + c->offset * c->block->rstride),
                     *c_pr1 = c_pr;
      for(i = 0; i < M; i++){
        c_pr = c_pr1;
        b->offset = B->offset;
        for(j =0; j < N; j++){
            *c_pr *= beta;
            *c_pr += alpha * vsip_vdot_f(a,b);
             c_pr += str;
             b->offset += B->row_stride;
        }  
        a->offset += A->col_stride;
        c_pr1 += str1;
      }
    }
  }  
}
