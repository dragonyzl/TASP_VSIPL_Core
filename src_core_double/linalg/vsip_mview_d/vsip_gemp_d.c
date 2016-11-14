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
/* $Id: vsip_gemp_d.c,v 1.1 1999/12/05 16:07:59 judd Exp judd $ */
/* vsip_gemp_d */
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip.h>
#include<VI_functions_d.h>

void (vsip_gemp_d)(vsip_scalar_d alpha,
                   const vsip_mview_d *AA,
                   vsip_mat_op OpA,
                   const vsip_mview_d *BB,
                   vsip_mat_op OpB,
                   vsip_scalar_d beta,
                   const vsip_mview_d *C){
vsip_mview_d At = *AA,
             Bt = *BB;
vsip_mview_d *A = &At,
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
    vsip_vview_d aa,bb,cc;
    vsip_vview_d *a = VI_mrowview_d(A,0,&aa),
                 *b = VI_mcolview_d(B,0,&bb),
                 *c = VI_mrowview_d(C,0,&cc);
    {
      vsip_stride str  = c->stride * c->block->rstride;
      vsip_stride str1 = C->col_stride * C->block->rstride;
      vsip_scalar_d  *c_pr =(vsip_scalar_d*) (c->block->array + c->offset * c->block->rstride),
                     *c_pr1 = c_pr;
      for(i = 0; i < M; i++){
        c_pr = c_pr1;
        b->offset = B->offset;
        for(j =0; j < N; j++){
            *c_pr *= beta;
            *c_pr += alpha * vsip_vdot_d(a,b);
             c_pr += str;
             b->offset += B->row_stride;
        }  
        a->offset += A->col_stride;
        c_pr1 += str1;
      }
    }
  }  
}
