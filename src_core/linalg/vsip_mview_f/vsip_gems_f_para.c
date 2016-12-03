/* $Id: vsip_gems_f.c,v 1.2 1999/12/02 18:43:16 judd Exp judd $ */
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
/* (C=alpha*op(AA)+beta*C) */
void (vsip_gems_f_para)(vsip_scalar_f alpha,
                   const vsip_mview_f *AA,
                   vsip_mat_op OpA,
                   vsip_scalar_f beta,
                   const vsip_mview_f *C){
   vsip_mview_f At = *AA;
   vsip_mview_f *A = &At;
   if(OpA == 1){
     A->row_length = AA->col_length;
     A->col_length = AA->row_length;
     A->row_stride = AA->col_stride;
     A->col_stride = AA->row_stride;
   }
   {
      vsip_length M = A->col_length;
      vsip_length N = A->row_length;
      vsip_length i,j;
      {
         vsip_stride Cst_C = C->col_stride * C->block->rstride;
         vsip_stride Cst_R = C->row_stride * C->block->rstride;
         vsip_stride Ast_C = A->col_stride * A->block->rstride;
         vsip_stride Ast_R = A->row_stride * A->block->rstride;
         vsip_scalar_f  *C_ptr =(vsip_scalar_f*) (C->block->array + C->offset * C->block->rstride),
                        *C_ptrR = C_ptr, /* pointer to row element zero */
                        *A_ptr =(vsip_scalar_f*) (A->block->array + A->offset * A->block->rstride),
                        *A_ptrR = A_ptr; /* pointer to row element zero */

         for(i = 0; i < M; i++){
             C_ptr = C_ptrR + i * Cst_C;
             A_ptr = A_ptrR + i * Ast_C;
#pragma omp parallel for
             for(j = 0; j < N; j++){
                 vsip_scalar_f *currentC = C_ptr + j * Cst_R;
                 vsip_scalar_f *currentA = A_ptr + j * Ast_R;
                *currentC = alpha * *currentA + beta * *currentC;
             }

         }


      }
   }  
}
