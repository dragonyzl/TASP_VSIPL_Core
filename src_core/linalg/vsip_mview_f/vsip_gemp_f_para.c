/* $Id: vsip_gemp_f.c,v 1.2 1999/12/02 18:43:15 judd Exp judd $ */
/* vsip_gemp_f */
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip.h>
#include<VI_functions_f.h>
#include<omp.h>

/*
typedef enum{
    VSIP_MAT_NTRANS = 0,
    VSIP_MAT_TRANS = 1,
    VSIP_MAT_HERM = 2,
    VSIP_MAT_CONJ = 3
} vsip_mat_op;
*/
/* (C=alpha*op(AA)op(BB) + beta*C) */
void (vsip_gemp_f_para)(vsip_scalar_f alpha,
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
    

vsip_offset b_off=b->offset;
vsip_offset a_off=a->offset;

#pragma omp parallel for private(j)
      for(i = 0; i < M; i++){
        c_pr = c_pr1 + i * str1;
        b->offset = B->offset;
        b_off=b->offset;
        a->offset = a_off + i * A->col_stride;

        vsip_scalar_f *currentc = c_pr;
        for(j =0; j < N; j++){
            b->offset = b_off + j * B->row_stride;
            *currentc = alpha * vsip_vdot_f_para(a,b) + beta*(*currentc);
            c_pr += str;
        }
      }


    }
  }  
}
